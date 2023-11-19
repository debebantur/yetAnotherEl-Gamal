#include <iostream>
#include <fstream>
#include <vector>

typedef long long ll;

using namespace std;

int pow(ll a, ll b, ll n){
    ll tmp=a;
    ll sum=a;
    for(ll i=1;i<b;++i){
        for(ll j=1;j<a;++j){
            sum+=tmp;
            if(sum>=n) sum-=n;
        }
        tmp=sum;
    }
    return tmp;
}

int multiply(ll a, ll b, ll n){
    ll sum=0;

    for(ll i=0;i<b;i++){
        sum+=a;
        if(sum>=n) sum-=n;
    }

    return sum;
}

ll getPrimeRoot(ll p){
    vector<ll> fact;
    ll phi = p-1,  n = phi;
    for (ll i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (ll res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= pow(res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

void crypt(int p,int g,int x, string name){
    ll y=pow(g,x,p);

    cout<<"Open key (p,g,y)="<<"( "<<p<<", "<<g<<", "<<y<<" )"<<endl;
    cout<<"Secret key x="<<x<<endl;

    cout<<"enter your message: ";
    ofstream out;
    out.open(name);

    string str;
    while(cin>>str){
        for(auto m : str){
                ll k=rand()%(p-2)+1; // 1 < k <= (p-2)
                ll a= pow(g, k, p);
                ll b= multiply(pow(y, k, p), m, p);
                out<<a<<" "<<b<<" ";
        }
        ll k=rand()%(p-2)+1; // 1 < k <= (p-2)
        ll a= pow(g,k,p);
        ll b= multiply(pow(y, k, p), ' ' ,p);
        out<<a<<" "<<b<<" ";
    }

   out.close();
}

void decrypt(int p,int x, string name){

    ifstream in;
    in.open(name);
    cout<<"start decryption"<<endl;

    ll a=0;
    ll b=0;
    while(in>>a>>b){
        if(a!=0&&b!=0){
            ll deM=multiply(b,pow(a,p-1-x,p),p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p
            char m=static_cast<char>(deM);
            cout<<m;
        }
    }
    cout<<endl;
    in.close();
}

int main()
{
    ll p, g, x;
    cout << "Enter prime p (997)" << endl;
    cin>>p;
    g = getPrimeRoot(p);
    cout << "Generated g for p: " << g<<endl;
    cout << "Enter secret key" << endl;
    cin>>x;
    crypt(p, g, x, "out.txt");
    cout << "Hello World!" << endl;
    decrypt(p, x, "out.txt");
    cout<<"ping"<<endl;
    cin>>p;
    return 0;
}
