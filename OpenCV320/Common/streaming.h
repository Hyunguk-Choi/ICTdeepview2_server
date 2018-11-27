//
// ��Ʈ���ֿ� ���õ� ������ �����Ѵ�.
//
#pragma once
#pragma pack(1)

namespace cvproc	
{
	enum TECHNOLOGYTYPE
	{
		DETECT1 = 0,
		DETECT2 = 1,
		FACE = 2,
		CAR_PEOPLE = 3,
		SOCIALFORCE = 4
	};

	struct OBJECT_DATA
	{
		int ObjectID;
		int x;
		int y;
		int Width;
		int Height;
		int Type;
		int DirectionFlag;
		int ntimes_updated;
		int Rank[3];
	};

	struct ICT_META_DATA
	{
		int CameraNumber;
		int FrameNumber;
		int TechnologyType;
		int NumberOfObject = 0;
		OBJECT_DATA* pObjectData;
	};

	struct sStreamingData
	{
		unsigned char id;			// streaming id (���� ���̵𳢸� ����Ÿ�� ��ģ �Ŀ� ����Ѵ�.)
		unsigned char chunkSize;	// chunk size (�̹��� �뷮 ������ ������ ����Ÿ ûũ�� ����)
		unsigned char chunkIndex;	// chunk index
		//unsigned char isGray;		// gray 0 : 1
		//unsigned char isCompressed;	// jpeg compressed 0 : 1
		int imageBytes;				// image size (byte unit)

		unsigned int CameraNumber;
		unsigned int FrameNumber;
		unsigned int TechnologyType;
		unsigned int NumberOfObject = 0;
		
		char* pObjectData;
		char *data;					// image data
	};


	const static int g_maxStreamSize = (int)pow(2, 20) - 1;
}
