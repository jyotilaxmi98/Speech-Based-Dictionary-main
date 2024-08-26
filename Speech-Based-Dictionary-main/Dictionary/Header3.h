//#include "stdafx.h"
#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
//#include<string.h>
// #pragma once

//using namespace std;





void Play()
{
	FILE* fp=fopen("predicted_word.txt","r");
	int x;
	fscanf(fp,"%d",&x);
	char A[10];
	sprintf(A,"%d.wav",x);
   wchar_t wtext[20];
  mbstowcs(wtext, A, strlen(A)+1);//Plus null
 LPWSTR ptr = wtext;
	//PlayRecord();
	PlaySound(ptr,NULL,SND_FILENAME);

}