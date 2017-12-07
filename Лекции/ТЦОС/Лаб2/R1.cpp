// Energy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define m 100 // ������ ����� ������� � ��������

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
	inf=fopen("D:\\Work\\MADSP_lab\\R1\\ck.wav","rb");
	outf=fopen("D:\\Work\\MADSP_lab\\R1\\ck_r1.wav","wb");
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
	short s,s1;			//������
	double sum,sum1;
	s1=0;
	for (int i=0; i<N/m; i++)
	{
		sum=0;
		sum1=0;
		
		for (int k=0; k<m; k++)
		{
			fread(&s,2,1,inf);
			s+=1000*((double)rand()/RAND_MAX-0.5);
			sum+=s*s;
			sum1+=s*s1;
			s1=s;
		}
		s=10000*sum1/sum;

		for (int k=0; k<m; k++)
			fwrite(&s,2,1,outf);
	}
	return 0;
}

