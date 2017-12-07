// Central.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "math.h"

int _tmain(int argc, _TCHAR* argv[])
{
	struct rifftype{ //��������� RIFF �����
		char id[4];		//������������� ����� = "RIFF" = 0x46464952
		long len;		//����� ����� ��� ����� ���������
	} IDRiff;

	struct chucktype{ //��������� ����� WAV
		char id[4];		//������������� = "WAVE" = 0x45564157
		char fmt[4];	//������������� = "fmt " = 0x20746D66
		long len;		//����� ����� ����� WAV - �����,
	} IDChuckWave;

	struct wavetype{ //����� WAV
        short type;				//��� �������� ������
        short channels;			//����� ������� 
        long SamplesPerSec;		//������� ������� 
        long AvgBytesPerSec;	//������� ������ ������ 
        short align;			//������������
        short bits;				//����� ��� �� �������  
	} IDWave;

	struct sampletype{ //������������� �������
		char id[4];		//������������� ="data" =0x61746164
        long len;		//����� ������� ( ������ 2 )
	} IDSampleWave;

	FILE *inf,*outf; 
	inf=fopen("D:\\Work\\MADSP_lab\\Central\\123.wav","rb");
	outf=fopen("D:\\Work\\MADSP_lab\\Central\\123_centr.wav","wb");
	if (inf==0)
	{
		return 0;
	}

	fread(&IDRiff,sizeof(IDRiff),1,inf);
	fread(&IDChuckWave,sizeof(IDChuckWave),1,inf);
	fread(&IDWave,sizeof(IDWave),1,inf);
	fread(&IDSampleWave,sizeof(IDSampleWave),1,inf);

	fwrite(&IDRiff,sizeof(IDRiff),1,outf);
	fwrite(&IDChuckWave,sizeof(IDChuckWave),1,outf);
	fwrite(&IDWave,sizeof(IDWave),1,outf);
	fwrite(&IDSampleWave,sizeof(IDSampleWave),1,outf);

	int N=IDSampleWave.len/2;		// ����� ������� � ��������
	short s;			//������

	int porog=6000;

	for (int i=0; i<N; i++)
	{
		fread(&s,2,1,inf);
		if (s<=-porog) s=s+porog;
			else 
				if (s>=porog) s=s-porog;
					else s=0;
		


		fwrite(&s,2,1,outf);
	}
	return 0;
}
