
#include "stdafx.h"
#include "streamingreceiver.h"


using namespace cvproc;


cStreamingReceiver::cStreamingReceiver() 
	: m_rcvBuffer(NULL)
	, m_sndBuffer(NULL)
{

}

cStreamingReceiver::~cStreamingReceiver()
{
	SAFE_DELETEA(m_rcvBuffer);
	SAFE_DELETEA(m_sndBuffer);
}


bool cStreamingReceiver::Init(const bool isUDP, const int bindPort, 
	const bool isConvertGray, const bool isCompressed, const int jpgQuality)
{
	m_isCompressed = isCompressed;
	m_jpgCompressQuality = jpgQuality;
	m_isConvertGray = isConvertGray;

	m_isUDP = isUDP;

	m_udpServer.Close();
	m_tcpServer.Close();
	
	if (isUDP)
	{
		m_udpServer.SetMaxBufferLength(307200);
		if (!m_udpServer.Init(0, bindPort))
			return false;
	}
	else
	{
		if (!m_tcpServer.Init(bindPort, g_maxStreamSize, 10, 10))
			return false;
	}

	if (m_src.empty())
		m_src = Mat(480, 640, CV_8UC1);
	if (m_finalImage.empty())
		m_finalImage = Mat(480, 640, CV_8UC1);

	if (!m_rcvBuffer)
		m_rcvBuffer = new char[g_maxStreamSize];

	m_state = READY;

	if (m_gray.empty())
		m_gray = Mat(480, 640, CV_8UC1);

	if (m_compBuffer.capacity() == 0)
		m_compBuffer.reserve(307200);

	if (!m_sndBuffer)
		m_sndBuffer = new char[g_maxStreamSize];

	m_iCount = 0;
	return true;
}


cv::Mat& cStreamingReceiver::Update()
{
	const static int sizePerChunk = g_maxStreamSize - sizeof(sStreamingData); // size per chunk

	int len = 0;
	if (m_isUDP)
	{
		len = m_udpServer.GetRecvData(m_rcvBuffer, g_maxStreamSize);
	}
	else
	{
		network::sPacket packet;
		if (m_tcpServer.m_recvQueue.Front(packet))
		{
			len = packet.actualLen;
			memcpy(m_rcvBuffer, packet.buffer, packet.actualLen);
			m_tcpServer.m_recvQueue.Pop();
		}
	}

	if (len <= 0)
		return m_finalImage;

	sStreamingData *packet = (sStreamingData*)m_rcvBuffer;
	/*static int oldCompressed = -1;
	static int oldGray = -1;
	if (oldCompressed != (int)packet->isCompressed)
	{
		oldCompressed = (int)packet->isCompressed;
		std::cout << "compressed = " << (int)packet->isCompressed << std::endl;
	}
	if (oldGray != (int)packet->isGray)
	{
		oldGray = (int)packet->isGray;
		std::cout << "gray = " << (int)packet->isGray << std::endl;
	}*/


	if (packet->chunkSize == 1)
	{
		packet->data = m_rcvBuffer + sizeof(sStreamingData);

		/*if (packet->isCompressed)
		{*/
			memcpy((char*)m_src.data, packet->data, packet->imageBytes);
			cv::imdecode(m_src, 1, &m_finalImage);
		//}
		//else
		//{
		//	// 바로 decode 에 복사해서 리턴한다.
		//	memcpy((char*)m_finalImage.data, packet->data, packet->imageBytes);
		//}
	}
	else if (packet->chunkSize > 1)
	{
		static unsigned char oldId = 0;

		if (oldId != packet->id)
		{
			/*if (packet->isCompressed)
			{*/
				cv::imdecode(m_src, 1, &m_finalImage);
			//}
			//else
			//{
			//	// 바로 decode 에 복사해서 리턴한다.
			//	memcpy((char*)m_finalImage.data, (char*)m_src.data, m_src.total() * m_src.elemSize());
			//}

			oldId = packet->id;
		}

		packet->data = m_rcvBuffer + sizeof(sStreamingData);
		char *dst = (char*)m_src.data + packet->chunkIndex * sizePerChunk;
		const int copyLen = max(0, (len - (int)sizeof(sStreamingData)));
		memcpy(dst, packet->data, copyLen);
	}

	return m_finalImage;
}

// image는 흑백 영상이어야 한다.
// 크기는 640/480 이어야 한다.
int cStreamingReceiver::Send(const cv::Mat &image)
{
	if (READY == m_state)
	{
		// 이미지를 변조한다.
		uchar *data = image.data;
		int buffSize = image.total() * image.elemSize();

		// Gray Scale
		if (m_isConvertGray)
		{
			cvtColor(image, m_gray, CV_RGB2GRAY);
			data = m_gray.data;
			buffSize = m_gray.total() * m_gray.elemSize();
		}

		// 압축
		if (m_isCompressed)
		{
			vector<int> p(3);
			p[0] = CV_IMWRITE_JPEG_QUALITY;
			p[1] = m_jpgCompressQuality;
			p[2] = 0;
			cv::imencode(".jpg", m_isConvertGray ? m_gray : image, m_compBuffer, p);
			data = (uchar*)&m_compBuffer[0];
			buffSize = m_compBuffer.size();
		}

		return SendImage(data, buffSize, m_isConvertGray, m_isCompressed);
	}
	else if (SPLIT == m_state)
	{
		if (SendSplit())
		{
			m_state = READY;
			++m_chunkId;
			if (m_chunkId > 100)
				m_chunkId = 0;
		}
	}

	return 0;
}


// 용량이 큰 데이타면, 분리해서 전송한다.
int cStreamingReceiver::SendImage(const BYTE *data, const int len,
	const bool isGray, const bool isCompressed)
{
	int NumberOfObject = (rand() % (10 - 1 + 1)) + 1;
	const int totalSize = len + sizeof(sStreamingData) + sizeof(OBJECT_DATA) + NumberOfObject;

	m_iCount++;
	if (m_iCount > 100)
		m_iCount = 0;

	if (totalSize < g_maxStreamSize)
	{
		if (m_iCount % 5 == 0) {
			NumberOfObject = (rand() % (10 - 1 + 1)) + 1;
		}
		else {
			NumberOfObject = 0;
		}
		sStreamingData *packet = (sStreamingData*)m_sndBuffer;
		OBJECT_DATA m_SendObject;
		packet->id = 0;
		packet->chunkSize = 1;
		packet->chunkIndex = 0;
		packet->imageBytes = len;
		packet->CameraNumber = 1;
		packet->FrameNumber = m_iCount;
		packet->NumberOfObject = NumberOfObject;
		packet->TechnologyType = 1;

		
		for (int i = 0; i < packet->NumberOfObject; i++) {
			packet->pObjectData = m_sndBuffer + sizeof(sStreamingData) + sizeof(OBJECT_DATA) * i;
			m_SendObject.DirectionFlag = 1;
			m_SendObject.Height = (rand() % (480 - 1 + 1)) + 1;
			m_SendObject.ntimes_updated = 1;
			m_SendObject.ObjectID = i + 1;
			m_SendObject.Type = 1;
			m_SendObject.Width = (rand() % (640 - 1 + 1)) + 1;
			m_SendObject.x = (rand() % (640 - 1 + 1)) + 1;
			m_SendObject.y = (rand() % (480 - 1 + 1)) + 1;

			memcpy(packet->pObjectData, &m_SendObject, sizeof(OBJECT_DATA));
		}
		

		//packet->isGray = isGray ? 1 : 0;
		//packet->isCompressed = isCompressed ? 1 : 0;
		packet->data = m_sndBuffer + sizeof(sStreamingData) + sizeof(OBJECT_DATA) * packet->NumberOfObject;
		memcpy(packet->data, data, len);

		if (m_isUDP)
			m_udpServer.SetRecvData((char*)packet, sizeof(sStreamingData) + sizeof(OBJECT_DATA) * packet->NumberOfObject + len);
		else
			m_tcpServer.Send((BYTE*)packet, sizeof(sStreamingData) + sizeof(OBJECT_DATA) * packet->NumberOfObject + len);
		return 1;
	}
	else
	{
		const int sizePerChunk = g_maxStreamSize - sizeof(sStreamingData); // size per chunk
		m_chunkCount = (len / sizePerChunk);
		if ((len % sizePerChunk) != 0)
			++m_chunkCount;

		m_sendChunkIndex = 0;
		m_sendBytes = 0;
		m_imagePtr = (BYTE*)data;
		m_imageBytes = len;
		SendSplit();

		m_state = SPLIT;
		return m_chunkCount;
	}
}


// 모든 청크를 전송했다면 true를 리턴한다.
bool cStreamingReceiver::SendSplit()
{
	const int sizePerChunk = g_maxStreamSize - sizeof(sStreamingData); // size per chunk

	sStreamingData *packet = (sStreamingData*)m_sndBuffer;
	packet->id = (unsigned char)m_chunkId;
	packet->chunkSize = m_chunkCount;
	packet->chunkIndex = m_sendChunkIndex;
	packet->imageBytes = m_imageBytes;
	packet->CameraNumber = 1;
	packet->FrameNumber = 1;
	packet->NumberOfObject = 1;
	packet->TechnologyType = 1;
	//packet->isGray = m_isConvertGray ? 1 : 0;
	//packet->isCompressed = m_isCompressed ? 1 : 0;
	packet->data = m_sndBuffer + sizeof(sStreamingData);

	int copyLen = 0;
	if (m_sendBytes + sizePerChunk > m_imageBytes)
	{
		copyLen = m_imageBytes%sizePerChunk;
		memcpy(packet->data, m_imagePtr + m_sendChunkIndex * sizePerChunk, copyLen);
	}
	else
	{
		copyLen = sizePerChunk;
		memcpy(packet->data, m_imagePtr + m_sendChunkIndex * sizePerChunk, copyLen);
	}

	if (m_isUDP)
		m_udpServer.SendData((BYTE*)packet, sizeof(sStreamingData) + copyLen);
	else
		m_tcpServer.Send((BYTE*)packet, sizeof(sStreamingData) + copyLen);

	m_sendBytes += sizePerChunk;
	++m_sendChunkIndex;

	if (m_sendBytes >= m_imageBytes)
		return true;

	return false;
}