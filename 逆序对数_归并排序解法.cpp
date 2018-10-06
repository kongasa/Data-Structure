//求逆序对数，归并排序解法
#include<cstdio>
#include<cstdlib>

#define ll long long

int buildings[100000];
int sorted[100000];
ll ans;

void merge(int left, int mid, int right){
    int left_count = left;
    int right_count = mid + 1;
    int k = left;
    while (left_count <= mid && right_count <= right){
        if (buildings[left_count] < buildings[right_count]){
            sorted[k++] = buildings[left_count++];
        }
        else{
            sorted[k++] = buildings[right_count++];
            ans += mid - left_count + 1;
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
    return 0;
}