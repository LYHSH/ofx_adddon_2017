#pragma once
/************************************************************************/
/* file describe:–£—È¬Îº∆À„
/* date:2018.11.12
/* author:hui
/************************************************************************/
unsigned char ofGetSumVerify(int nStart, int nEnd, const unsigned char * _dataCode);
unsigned short ofCRC166(unsigned char *puchMsg, unsigned short usDataLen);
unsigned char ofGetSumVerifySub(int nStart, int nEnd, const unsigned char * _dataCode);
