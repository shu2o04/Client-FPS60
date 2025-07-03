#pragma once

void InitEncDec();
FILE *EncDecOpenFile(const char *path, const char *f);
int EncDecCheckFile(FILE *hFile);
BOOL EncDecDecryptFile(FILE *hFile, BYTE *Buffer, int Size, int Origin, int Offset);
void EncDecOpenJpegBuffer1();
void EncDecOpenJpegBuffer2();
void EncDecOpenTga();
void EncDecOpenBmd();
void EncDecOpenAtt();
void EncDecOpenMap();
void EncDecOpenObj();
