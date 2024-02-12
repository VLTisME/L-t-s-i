#include <bits/stdc++.h>

  using namespace std;

  #define ll long long
  #define f first
  #define s second

  typedef pair <int, int> ii;

  const int N = 1e5;
  const int M = 2e4;
  const int S = 316;
  const int MOD = 998244353;

  int n, q;
  int seg[4 * N + 5];
  bool lazy[4 * N + 5];

  void pass(int lo, int hi, int pos){
       if (lazy[pos]){
           int mid = (lo + hi) / 2;
           lazy[pos] = 0;
           if (lo != hi){
               lazy[pos * 2] ^= 1;
               lazy[pos * 2 + 1] ^= 1;
               seg[pos * 2] = (mid - lo + 1) - seg[pos * 2];
               seg[pos * 2 + 1] = (hi - mid) - seg[pos * 2 + 1];
           }     
       }
  }

  void update(int qlo, int qhi, int lo, int hi, int pos){
       pass(lo, hi, pos);
       if (lo > qhi || hi < qlo) return;
       if (qlo <= lo && qhi >= hi){
           lazy[pos] = 1;
           seg[pos] = (hi - lo + 1) - seg[pos];
           return;
       }
       int mid = (lo + hi) / 2;
       update(qlo, qhi, lo, mid, pos * 2);
       update(qlo, qhi, mid + 1, hi, pos * 2 + 1);
       seg[pos] = seg[pos * 2] + seg[pos * 2 + 1];
  }

  int get(int qlo, int qhi, int lo, int hi, int pos){
      pass(lo, hi, pos);
      if (lo > qhi || hi < qlo) return 0;
      if (qlo <= lo && qhi >= hi) return seg[pos];
      int mid = (lo + hi) / 2;
      return get(qlo, qhi, lo, mid, pos * 2) + get(qlo, qhi, mid + 1, hi, pos * 2 + 1);
  }

  void solve(){
       cin >> n >> q;
       for (int tc = 1, t, A, B; tc <= q; ++tc){
            cin >> t >> A >> B;
            ++A, ++B;
            if (t){
                cout << get(A, B, 1, n, 1) << "\n";
            }
            else{
                update(A, B, 1, n, 1);
            }
       }
  }


  signed main(){
         //freopen("TRAVEL.INP","r", stdin);
         //freopen("TRAVEL.OUT","w", stdout);
         ios::sync_with_stdio(0);
         cin.tie(0);
         int test = 1;
         if (0) cin >> test;
         while (test--){
                solve();
                cout << "\n";
         }
         //cerr << double(sizeof(sum) + sizeof(dp)) / (1 << 20); 
     }