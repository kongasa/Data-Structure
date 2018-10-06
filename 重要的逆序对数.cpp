//求逆序对数，归并排序解法
#include<cstdio>
#include<cstdlib>

#define ll long long

const int MAX_LENGTH = 200005;
int buildings[MAX_LENGTH];
int sorted[MAX_LENGTH];
int right_range[MAX_LENGTH];
ll ans;

int binary_search(int start, int end, int value){
    int left = start;
    int right = end;
    int mid;
    while (left < right){
        mid = (left + right + 1) >> 1;
        if (value < (buildings[mid] + 1) / 2){
            right = mid - 1;
        }
        else{
            left = mid;
        }
    }
    if (value < (buildings[left] + 1) / 2) return end - right + 1;
    else return end - right;
}

void merge(int left, int mid, int right){
    int left_count = left;
    int right_count = mid + 1;
    int k = left;
    while (left_count <= mid && right_count <= right){
        if (buildings[left_count] < buildings[right_count]){
            sorted[k++] = buildings[left_count++];
        }
        else{
            ans += binary_search(left_count, mid, buildings[right_count]);
            sorted[k++] = buildings[right_count++];
        }
    }
    while (left_count <= mid){
        sorted[k++] = buildings[left_count++];
    }
    while (right_count <= right){
        sorted[k++] = buildings[right_count++];
    }

    for (k = left; k <= right; ++k){
        buildings[k] = sorted[k];
    }
}

void solve(int left, int right){
    if (left >= right) return;

    int mid = (left + right) >> 1;
    solve(left, mid);
    solve(mid + 1, right);
    merge(left, mid, right);
}

int main(){
    int n;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i){
        scanf("%d", &buildings[i]);
    }
    solve(0, n - 1);
    printf("%lld", ans);
    system("pause");
    return 0;
}