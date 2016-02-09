int select(int a[],int size,int x){
    int low=0,high=size-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(x<a[mid])
            high=mid-1;
        else if(x>a[mid])
            low=mid+1;
        else
            return mid;
    }
    return -1;
}
