//
// Protocol
//	- (byte) chunk size (�̹��� �뷮 ������ ������ ����Ÿ ûũ�� ����)
//	- (byte) chunk index
//	- (byte) gray 0 : 1
//	- (byte) compressed 0 : 1
//	- (int) image size
//
#pragma once

#include "streaming.h"


namespace cvproc
{
	class cStreamingReceiver
	{
	public:
		cStreamingReceiver();
		virtual ~cStreamingReceiver();

		bool Init(const bool isUDP, const int bindPort,
			const bool isConvertGray = false, const bool isCompressed = true, const int jpgQuality = 40);
		cv::Mat& Update();


		network::cUDPServer m_udpServer;
		network::cTCPServer m_tcpServer;
		bool m_isUDP;
		cv::Mat m_src;
		cv::Mat m_finalImage;		// ���� �̹���
		char *m_rcvBuffer;

		int Send(const cv::Mat &image);

		bool m_isConvertGray;
		bool m_isCompressed;
		int m_jpgCompressQuality;
		std::vector<uchar> m_compBuffer;
		cv::Mat m_gray;
		char *m_sndBuffer;

		int m_iCount;
	protected:
		int SendImage(const BYTE *data, const int len, const bool isGray, const bool isCompressed);
		bool SendSplit();

	protected:
		enum STATE {
			NOTCONNECT,	// ������ ���ӵǾ� ���� ���� ����
			READY,	// �̹��� ������ ������ ����
			SPLIT,	// �̹����� �������� ûũ�� ����� ������ ����
		};
		STATE m_state;

						// Send Split Parameters
		BYTE *m_imagePtr;
		int m_chunkId;
		int m_sendChunkIndex;
		int m_chunkCount;
		int m_imageBytes;
		int m_sendBytes;
	};
}
