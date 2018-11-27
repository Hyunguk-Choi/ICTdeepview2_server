
#include "stdafx.h"
#include "udpserver.h"
#include <iostream>
#include <process.h> 

using namespace network;

unsigned WINAPI UDPServerThreadFunction(void* arg);


cUDPServer::cUDPServer() 
	: m_id(0)
	, m_isConnect(false)
	, m_threadLoop(true)
	, m_bufferLen(0)
	, m_maxBuffLen(BUFFER_LENGTH)
	, m_sndBuffLen(0)
	, m_isSendData(false)
{
	InitializeCriticalSectionAndSpinCount(&m_CriticalSection, 0x00000400);
	m_buffer = new char[m_maxBuffLen];
	m_sndBuffer = new BYTE[m_maxBuffLen];
}

cUDPServer::~cUDPServer()
{
	m_threadLoop = false;

	::WaitForSingleObject(m_handle, 1000);

	DeleteCriticalSection(&m_CriticalSection);
	closesocket(m_socket);

	delete[] m_buffer;
	delete[] m_sndBuffer;
}


bool cUDPServer::Init(const int id, const int port)
{
	m_id = id;
	m_port = port;

	if (m_isConnect)
	{
		closesocket(m_socket);
		m_isConnect = false;
		m_threadLoop = false;
	}
	else
	{
		std::cout << "Bind UDP Server port = " << port << std::endl;

		if (network::LaunchUDPServer(port, m_socket))
		{
			m_isConnect = true;
			m_threadLoop = true;
			m_handle = (HANDLE)_beginthreadex(NULL, 0, UDPServerThreadFunction, this, 0, (unsigned*)&m_threadId);
		}
		else
		{
			return false;
		}
	}

	return true;
}

// 전송할 정보를 설정한다.
void cUDPServer::SendData(const BYTE *buff, const int buffLen)
{
	EnterCriticalSection(&m_CriticalSection);
	m_sndBuffLen = min(buffLen, m_maxBuffLen);
	memcpy(m_sndBuffer, buff, m_sndBuffLen);
	m_isSendData = true;
	LeaveCriticalSection(&m_CriticalSection);
}

void cUDPServer::SetRecvData(const char *buff, const int buffLen)
{
	EnterCriticalSection(&m_CriticalSection);
	memcpy(m_buffer, buff, buffLen);
	m_bufferLen = buffLen;
	m_isReceiveData = true;
	LeaveCriticalSection(&m_CriticalSection);
}


// 받은 패킷을 dst에 저장해서 리턴한다.
// 동기화 처리.
int cUDPServer::GetRecvData(OUT char *dst, const int maxSize)
{
	EnterCriticalSection(&m_CriticalSection);
	int buffLen = 0;
	if (maxSize < m_bufferLen)
	{
		LeaveCriticalSection(&m_CriticalSection);
		return 0;
	}

	if (!m_isReceiveData || (m_bufferLen <= 0))
	{
		m_isReceiveData = false;
		LeaveCriticalSection(&m_CriticalSection);
		return 0;
	}

	memcpy(dst, m_buffer, m_bufferLen);
	buffLen = m_bufferLen;
	m_isReceiveData = false;
	LeaveCriticalSection(&m_CriticalSection);
	return buffLen;
}


void cUDPServer::Close(const bool isWait) // isWait = false
{
	m_threadLoop = false;
	if (isWait)
	{
		::WaitForSingleObject(m_handle, INFINITE);
	}
	m_isConnect = false;
	closesocket(m_socket);
}


void cUDPServer::SetMaxBufferLength(const int length)
{
	if (m_maxBuffLen != length)
	{
		delete[] m_buffer;
		delete[] m_sndBuffer;

		m_maxBuffLen = length;
		m_buffer = new char[length];
		m_sndBuffer = new BYTE[length];
	}
}


// void PrintBuffer(const char *buffer, const int bufferLen)
// {
// 	for (int i = 0; i < bufferLen; ++i)
// 		printf("%c", buffer[i]);
// 	printf("\n");
// }


// UDP 서버 쓰레드
unsigned WINAPI UDPServerThreadFunction(void* arg)
{
	cUDPServer *udp = (cUDPServer*)arg;
	const int sleepMillis = 1;

	char *buff = new char[udp->m_maxBuffLen];

	int recv_len;
	char *sndBuff = new char[udp->m_maxBuffLen];

	memset(sndBuff, '\0', udp->m_maxBuffLen);

	while (udp->m_threadLoop)
	{
		// Send
		bool isSend = false;
		EnterCriticalSection(&udp->m_CriticalSection);
		if (udp->m_isSendData)
		{
			memcpy(sndBuff, udp->m_sndBuffer, udp->m_sndBuffLen);
			recv_len = udp->m_sndBuffLen;
			udp->m_isSendData = false;
			isSend = true;
		}
		LeaveCriticalSection(&udp->m_CriticalSection);

		if (isSend)
		{
			if (send(udp->m_socket, (char*)sndBuff,
				recv_len, 0) == SOCKET_ERROR)
			{
				int a = 0;
				//printf("sendto() failed with error code : %d", WSAGetLastError());
				//exit(EXIT_FAILURE);
			}
		}

		const timeval t = { 0, 1 }; // 10 millisecond
		fd_set readSockets;
		FD_ZERO(&readSockets);
		FD_SET(udp->m_socket, &readSockets);

		const int ret = select(readSockets.fd_count, &readSockets, NULL, NULL, &t);
		if (ret != 0 && ret != SOCKET_ERROR)
		{
			//char buff[cUDPServer::BUFFER_LENGTH];
			const int result = recv(readSockets.fd_array[0], buff, udp->m_maxBuffLen, 0);
			if (result == SOCKET_ERROR || result == 0) // 받은 패킷사이즈가 0이면 서버와 접속이 끊겼다는 의미다.
			{
// 				closesocket(udp->m_socket);
// 				udp->m_threadLoop = false;
// 				udp->m_isConnect = false;
			}
			else
			{
				udp->SetRecvData(buff, result);
			}
		}

		Sleep(sleepMillis);
	}

	delete[] buff;
	return 0;
}
