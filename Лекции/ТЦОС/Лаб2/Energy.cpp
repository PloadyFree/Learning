// Energy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "math.h"

#define m 200 // ������ ����� ������� � ��������

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
	inf=fopen("D:\\Work\\MADSP_lab\\Energy\\10.wav","rb");
	outf=fopen("D:\\Work\\MADSP_lab\\Energy\\10_Eng.wav","wb");
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
	double sum;

	for (int i=0; i<N/m; i++)
	{
		sum=0;
		for (int k=0; k<m; k++)
		{
			fread(&s,2,1,inf);

//			sum+=labs(s);
//			sum+=abs(s);
			sum+=s*s;

		}
//		s=1*sum/m;
		s=1000*log10(0.01+sum/m);

		for (int k=0; k<m; k++)
			fwrite(&s,2,1,outf);
	}
	return 0;
}

