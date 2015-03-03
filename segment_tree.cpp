#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#define ll long long int
using namespace std;
ll size_of_segtree;

void recursive_update(ll *seg_tree,ll start,ll end,ll index,ll diff,ll seg_index)
{
	if(index<start || index>end)
		return;

	seg_tree[seg_index]=seg_tree[seg_index]+diff;

	if(start!=end)
	{
		ll mid=start+(end-start)/2;
		recursive_update(seg_tree,start,mid,index,diff,2*seg_index+1);
		recursive_update(seg_tree,mid+1,end,index,diff,2*seg_index+2);
	}	
}

void update(ll *arr,ll n,ll *seg_tree,ll index,ll new_val)
{
	if(index<0 || index>n-1)
	{
		printf("\nInvalid range\n");
		return;
	}
	ll diff=new_val-arr[index];
	arr[index]=new_val;
	recursive_update(seg_tree,0,n-1,index,diff,0);
}

ll recursive_sum(ll *seg_tree,ll start,ll end,ll x,ll y,ll seg_index)
{
	//if segment of this node is a part of given range then return
	if(x<=start && end<=y)
		return seg_tree[seg_index];

	//if segment of this node is outside of the given range
	if(end<x || y<start)
		return 0;

	ll mid=start+(end-start)/2;
	return recursive_sum(seg_tree,start,mid,x,y,2*seg_index+1)
		  + recursive_sum(seg_tree,mid+1,end,x,y,2*seg_index+2);
}

ll givesum(ll *seg_tree,ll n,ll x,ll y)
{
	//checking for outofbound condition
	if(x<0 || y>n-1 || x>y)
	{
		printf("\nInvalid range]\n");
		return -1;
	}

	ll sum=recursive_sum(seg_tree,0,n-1,x,y,0);

	return sum;
}

ll recursive_construct(ll *arr,ll arr_start,ll arr_end,ll *seg_tree,ll seg_index)
{
	if(arr_start==arr_end)
	{
		seg_tree[seg_index]=arr[arr_start];
		return arr[arr_start];
	}
	
	ll mid=arr_start+(arr_end-arr_start)/2;
	seg_tree[seg_index]=recursive_construct(arr,arr_start,mid,seg_tree,2*seg_index+1)
						+ recursive_construct(arr,mid+1,arr_end,seg_tree,2*seg_index+2);

	return seg_tree[seg_index];
}

ll * construct_seg_tree(ll *arr,ll n)
{
	int height=(int)(ceil(log2(n)));	//height of seg_tree
	ll maxsize=2*(ll)pow(2,height)-1;	//maxsize of seg_tree
	ll *seg_tree=(ll *)calloc(maxsize,sizeof(ll));
	size_of_segtree=maxsize;

	recursive_construct(arr,0,n-1,seg_tree,0);

	return seg_tree;
}

int main()
{
	ll *arr;
	ll size,i;
	scanf("%lld",&size);
	arr=(ll *)calloc(size,sizeof(ll));
	for(i=0;i<size;i++)
		scanf("%lld",&arr[i]);
	
	ll *seg_tree=construct_seg_tree(arr,size);

	printf("\nSegmented tree:\n");
	for(i=0;i<size_of_segtree;i++)
		printf("%lld\t",seg_tree[i]);
	printf("\n\n");

	ll x,y;		//here x and y are index value starting from 0
	printf("specify range x and y:\t");
	scanf("%lld %lld",&x,&y);
	printf("sum of values in given range:\t%lld\n",givesum(seg_tree,size,x,y));

	ll index,new_val;
	printf("specify index and new value for that element:\t");
	scanf("%lld %lld",&index,&new_val);
	update(arr,size,seg_tree,index,new_val);
	printf("\nUpdated Segmented tree:\n");
	for(i=0;i<size_of_segtree;i++)
		printf("%lld\t",seg_tree[i]);
	printf("\n");
	return 0;
}