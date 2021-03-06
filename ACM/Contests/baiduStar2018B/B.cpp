#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
typedef long long LL;

#define LOCAL

int main() {
#ifdef LOCAL
  ifstream cin("B.in");
  ofstream cout("B.out");
  LL start = clock();
#endif
  ios::sync_with_stdio(false);

#ifdef LOCAL
  LL end = clock();
  cerr << 1.0 * (end - start) / CLOCKS_PER_SEC << endl;
#endif
  return 0;
}
/**
1002 hex 題解

這題是倍增法 RMQ 跟位元 DP
的組合。本題解會先討論化簡成一維陣列後的題目，再討論倍增法在六邊形中要如何操作。
一維的 case

假設本題發生在一維的矩陣上，也就是說，輸入從六邊形的結構變成一個一維的矩陣，每一個詢問都給定一個矩陣上的連續區間。

假設矩陣的長度為 NNN，可以利用 O(NlogN)O(N \log N)O(NlogN) 的時間預處理，把
對於每個起點，長度為 2 的冪次 的區間的答案算出來，之後對於每個查詢可以用
O(1)O(1)O(1) 的時間處理。
表達顏色集合的方法

對於一個區間，我們可以用一個 646464
位元的整數來代表這個區間包含有哪些顏色，假設這個區間有第 iii
種顏色，那這個整數第 iii 個 bit 就為 111，反之則為
000。如果要對兩個區間的顏色取交集的話，把代表兩個區間的整數取 bitwise or
即可。最後要找出真正的答案時，就計算這個整數有幾個 bit 為 111
即可，這一步可以做到 O(log64)O(\log 64)O(log64) (這邊的 646464
為整數的位元數)，但是因為 646464 是常數，在本題解裡將會把這步視為 O(1)O(1)O(1)。
預處理

對於每個 2 的冪次 的長度，枚舉每一個起點去計算其答案。當長度為 20=12^0 =
12​0​​=1 時，答案為自己本身有的顏色。而對於長度為 2i2^i2​i​​
時，每個起點的答案可以藉由兩個 2i−12^{i-1}2​i−1​​
的區間取交集求出。對於一個特定的長度所花的時間為 O(N)O(N)O(N)，而我們總共有
logN\log NlogN 種長度 (因為是 2 的冪次)，所以預處理的時間為 O(NlogN)O(N \log
N)O(NlogN)。
求解答

對於一個區間的詢問，假設此詢問長度為 XXX，第一步是找出小於等於 XXX 的最大的 2
的冪次 YYY (例如小於等於 777 的最大 2 的冪次為
444)。然後再把這個區間分成兩個區間，這兩個區間的長度皆為
YYY，其中一個的起點跟詢問的區間一樣，另外一個的終點跟詢問的區間一樣，注意這兩個區間有可能有重疊。分出來的兩個區間有一個性質，就是其交集會跟原始詢問的區間一致，所以對於詢問的答案就可以用這兩個區間的答案
(已經預處理完了) 來取交集。
原始題目

六邊形上面也可以用倍增法！但是在預處理 2i2^i2​i​​ 的時候，我們要考慮 666
個長度為一半 2i−12^{i-1}2​i−1​​ 的子六邊形，以及最中心的一個點，共 777
個地方，才能完整覆蓋長度為 2i2^i2​i​​ 的六邊形。因為 777
依然是常數，所以預處理的時間複雜度還是 起點數量 乘上 logL\log
LlogL。而在對詢問求答案的時候只要考慮 666 個長度為最大的 2
的冪次子六邊形即可完整覆蓋詢問的六邊形，也是可以在 O(1)O(1)O(1) 內作完！

整體時間複雜度為 O(L2logL+Q)O(L^2\log L + Q)O(L​2​​logL+Q)。
另解

也可以使用 2L−12L-12L−1 個線段樹，每次詢問時走訪每一個線段樹，這樣時間複雜度為
O(QLlogL)O(QL\log L)O(QLlogL)。
*/