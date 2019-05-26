#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

void zeros(float *arr, int num_element)
{
    for (int i=0; i<num_element; i++)
        arr[i]=0.0;
}

//int m = 3, n = 6;
int m, n;

/*float A[3][6]={
    {-1, 1, 2, 1, 0, 0},
    {1, 2, -1, 0, 1, 0},
    {3, -1, 2, 0, 0, 1}
};*/
float **A;
//float C_all[6] = {3, -2, 1, 0, 0, 0};
float* C_all;
//string X[6] = {"x1", "x2", "x3", "x4", "x5", "x6"};
string* X;
//string X_real[3] = {"x1", "x2", "x3"};
string* X_real;
//string X_cs[3] = {"x4", "x5", "x6"};
string* X_cs;
int num_X_cs;
int num_X_real;
//float* B={6, 5, 14};
float* B;
float* delta;
float* C;
float* lamda;
float S=0;

float cal_S()
{
    float result = 0.0;
    for (int it=0; it<m; it++)
    {
        float c = C[it];
        float b = B[it];
        result += c*b;
    }
    return result;
}

float cal_delta(int i)
{
    float result = 0;
    for (int it=0; it<m; it++)
    {
        float c = C[it];
        float d = A[it][i];
        result += c*d;
    }
    result -= C_all[i];
    return result;
}

bool kduong(float *x, int num_element)
{
    for (int it=0; it<num_element; it++)
        if (x[it]>0) return false;
    return true;
}

int find_max(float *x, int num_element)
{
    float maxx = 0.0;
    int pos = -1;
    for (int it=0; it<num_element; it++)
    {
        if (x[it] >= maxx)
        {
            pos = it;
            maxx = x[it];
        }
    }
    return pos;
}

int find_duong_min(float *x, int num_element)
{
    float minn = 999.9;
    int pos = -1;
    for (int it=0; it<num_element; it++)
    {
        if (x[it] <= minn && x[it]>0)
        {
            pos = it;
            minn = x[it];
        }
    }
    return pos;
}

void update_lamda(int column)
{
    for (int it=0; it<m; it++)
    {
        float t = A[it][column];
        if (t!=0)
            lamda[it] = B[it]/t;
        else
            lamda[it] = -99.9;
    }
}

void update_AB_havepivot(int row, float pivot)
{
    for (int it=0; it<n; it++)
        A[row][it] = A[row][it]/pivot;
    B[row] = B[row]/pivot;
}

void update_AB_nopivot(int row, int column)
{
    for (int rw=0; rw<m; rw++)
    {
        if (rw != row)
        {
            float d = A[rw][column];
            for (int it=0; it<n; it++)
                A[rw][it] = A[rw][it] - d*A[row][it];

            B[rw] = B[rw] - d*B[row];
        }
    }
}

int index_in_X_cs(string a)
{
    for (int it=0; it<num_X_cs; it++)
        if (X_cs[it]==a)
            return it;
    return -1;
}

int main()
{
    int num_x;
    cout<<"Nhap so an x: "; cin>>num_x;
    cout<<"Nhap so bat phuong trinh dieu kien: "; cin>>m;
    n = num_x + m;

    num_X_cs = m;
    num_X_real = num_x;

    delta = new float(n);
    C = new float(m);
    lamda = new float(m);

    X = new string [n];
    for (int i=1; i<=n; ++i)
    {
        string s = "x";
        s += i+'0';
        X[i-1] = s;
    }
    X_real = new string [num_x];
    for (int i=1; i<=num_x; ++i)
    {
        string s = "x";
        s += i+'0';
        X_real[i-1] = s;
    }
    X_cs = new string [m];
    for (int i=num_x+1, t=0; i<=n; ++i)
    {
        string s = "x";
        s += i+'0';
        X_cs[t++]=s;
    }

    A = new float* [m];
    B = new float [m];
    for (int i=0; i<m; ++i)
    {
        A[i] = new float [n];
        zeros(A[i], n);
    }
    C_all = new float [n];
    zeros(C_all, n);
    cout<<"Nhap he so ham so toi uu(ham min):"<<endl;
    for (int i=0; i<num_x; i++)
        cin>>C_all[i];

    for (int i=0; i<m; ++i)
    {
        cout<<"Nhap he so bat phuong trinh dieu kien "<<i+1<<endl;
        for (int j=0; j<num_x; ++j)
        {
            float x_val;
            cin>>x_val;
            A[i][j] = x_val;
        }
        A[i][num_x+i] = 1;
        cout<<"b = "; cin>>B[i];
    }



    cout<<endl<<"---------Solution-----------"<<endl;
    //for int
    zeros (delta, n);
    zeros (C, m);
    zeros (lamda, m);

    int count_loop=0;
    while (true)
    {
        cout<<endl<<"loop: "<<count_loop<<endl;
        for (int it=0; it<n; it++)
            delta[it] = cal_delta(it);

        if (!kduong(delta, n))
        {
            int column = find_max(delta, n);
            update_lamda(column);
            int row = find_duong_min(lamda, m);
            if (row==-1)
            {
                cout<<"vo nghiem"<<endl;
                break;
            }
            cout<<X_cs[row]<<" ra ; "<<X[column]<<" vao"<<endl;
            X_cs[row] = X[column];
            C[row] = C_all[column];

            float pivot = A[row][column];
            cout<<"Pivot: "<<pivot<<endl;
            update_AB_havepivot(row, pivot);
            S = cal_S();
        }
        else
        {
            cout<<"Done, Z = "<<S<<endl;
            for (int it=0; it<num_X_real; it++)
            {
                int index = index_in_X_cs(X_real[it]);
                if (index != -1)
                    cout<<X_real[it]<<":"<<B[index]<<endl;
                else
                    cout<<X_real[it]<<":"<<0<<endl;
            }
            break;
        }

        count_loop++;
    }
    cout<<"So buoc lap: "<<count_loop+1<<endl;

    delete[] B;
    delete[] C_all;
    delete[] C;
    delete[] lamda;
    delete[] delta;
    delete[] X;
    delete[] X_real;
    delete[] X_cs;
    for (int i=0; i<n; ++i)
        delete[] A[i];
    delete[] A;

    return 0;
}
