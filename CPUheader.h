
// Danh sách các hàm sẽ sử dụng khi mã hóa - giải mã bằng CPU

int getSBoxValue(int num);

int get_ISBoxValue(int num);

void KeyExpansion();

void AddRoundKey(int round);

void SubBytes();

void Inv_SubBytes();

void ShiftRows();

void Inv_ShiftRows();

int gfmultby01(int b);

int gfmultby02(int b);

int gfmultby03(int b);

int gfmultby09(int b);

int gfmultby0b(int b);

int gfmultby0d(int b);

int gfmultby0e(int b);

void MixColumns();

void InvMixCoLumns();

void Hex(int n, int i);

void Cipher();

void Inv_Cipher();