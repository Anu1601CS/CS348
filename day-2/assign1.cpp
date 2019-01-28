#include<bits/stdc++.h>
#define SYNC ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
#define mp make_pair
#define pb push_back
typedef pair< pair<double,double> ,int > pfi;

struct src
{
	double send_rt;
	int bnd_width;
};

double func(double rt,double r1)
{
	double r2=(-1/rt)*(log(1-r1));
	return r2;
}

bool cmp2(const pair<double,pair<double,int> > &p1, const double v)
{
	if(p1.first<v)
		return true;
	else
		return false;
}

int main()
{
	SYNC
	int num=3;
	vector<double> v1;
	vector<double> v2;
	vector<double> v3;

	double tm;
	printf("Sources: 3\n");
	printf("Enter bandwidth(bits/sec) of each source: \n");
	struct src tmp[num+1];
	int i=1;

	for(i=1;i<=num;i++)
	{
		int y1;
		scanf("%d",&y1);
		tmp[i].bnd_width=y1;
	}

	printf("Enter bandwidth(bits/sec) of sink: ");
	int x1_1;
	scanf("%d",&x1_1);
	int sink_wid=x1_1;
	printf("Enter packet size(in bits): ");
	int pkt;
	scanf("%d",&pkt);
	printf("Enter simulation time(in sec):\n");
	scanf("%lf",&tm);
	double k1=0.0;

	priority_queue<pfi,vector<pfi>,greater<pfi> > pq;

	for(;k1<=20;k1=k1+0.5)
	{
		double x1;
		x1=(double)k1;
		tmp[1].send_rt=x1;
		tmp[2].send_rt=x1+0.5;
		tmp[3].send_rt=x1+1;

		int cnt[num+1];
		double sum[num+1];
		for(i=1;i<=num;i++)	sum[i]=0.0;
		memset(cnt,0,sizeof(cnt));
		int j=1;
		int pkt_loss[num+1];
		memset(pkt_loss,0,sizeof(cnt));

	double snk_sp=((double)pkt)/((double)sink_wid);
	for(i=1;i<=num;i++)
	{
		double sp=((double)pkt)/((double)tmp[i].bnd_width);
		double x2=0.0;
		double tm1=0.0;
		srand((long)time(NULL));

		for(;x2<tm;)
		{
			if(x2==0.0)
			{
				pq.push(mp(mp(sp,sp),i));
				x2=sp;
				sum[i]+=sp;
				cnt[i]++;
			}
			else
			{
				pfi p1=pq.top();
				if(x2<tm1)
				{
					x2=tm1;
					pq.push(mp(mp(x2+sp,sp),i));
				}
				else
				{
					sum[i]+=(abs(x2-tm1));
					pq.push(mp(mp(x2+sp,sp+x2-tm1),i));
				}
				sum[i]+=sp;
				x2+=sp;
				cnt[i]++;
			}

			double r1=rand()/(double)RAND_MAX;
			tm1+=func(tmp[i].send_rt,r1);
		}
	}

 	double x2=0.0;
 	j=1;
 	int sz=100;

 	double tmp_tm=0.0;
 	vector< pair<double,pair<double,int> > > v_ans;

 	while(!pq.empty())
	{
		pfi p1=pq.top();
		if(j==1)
		{
			if(p1.first.first+snk_sp<=tm)
			{
				sum[p1.second]+=(snk_sp);
				v_ans.pb(mp(p1.first.first,mp(p1.first.first,p1.second)));
			}
			else
			{
				sum[p1.second]-=p1.first.second;
				cnt[p1.second]--;
			}
			x2=(snk_sp)+p1.first.first;
		}
		else
		{
			if(p1.first.first>=x2)
			{
				if(p1.first.first+snk_sp<=tm)
				{
					sum[p1.second]+=(snk_sp);
					v_ans.pb(mp(p1.first.first,mp(p1.first.first,p1.second)));
				}
				else
				{
					sum[p1.second]-=p1.first.second;
					cnt[p1.second]--;
				}
				x2=p1.first.first;
			}
			else
			{
				if(p1.first.first+snk_sp+abs(x2-p1.first.first)<=tm)
				{
					sum[p1.second]+=(snk_sp)+abs(x2-p1.first.first);
					v_ans.pb(mp(x2,mp(p1.first.first,p1.second)));
				}
				else
				{
					sum[p1.second]-=p1.first.second;
					cnt[p1.second]--;
				}
			}
			x2+=snk_sp;
		}
		tmp_tm=p1.first.first;
		j++;
		pq.pop();
	}


	for(i=sz;i<v_ans.size();i++)
	{
		if(lower_bound(v_ans.begin(),v_ans.end(),v_ans[i].second.first,cmp2)!=v_ans.end())
		{
			int j=lower_bound(v_ans.begin(),v_ans.end(),v_ans[i].second.first,cmp2)-v_ans.begin();
			if(abs(j-i)>sz)	pkt_loss[v_ans[i].second.second]++;
		}
	}


	for(i=1;i<=num;i++)
	{
		if(i==1){
			if(cnt[i]==0)	v1.push_back((double)0);
			else	v1.push_back(pkt_loss[i]/(double)cnt[i]);
		}
		else if(i==2)
		{
			if(cnt[i]==0)	v2.push_back((double)0);
			else	v2.push_back(pkt_loss[i]/(double)cnt[i]);
		}
		else
		{
			if(cnt[i]==0)	v3.push_back((double)0);
			else	v3.push_back(pkt_loss[i]/(double)cnt[i]);
		}
	}

	}

	printf("The average delay of the sources are (1 to n):\n");
	cout<<"Source 1\n";
	for(i=0;i<v1.size();i++)
		cout<<v1[i]<<"\n";
	cout<<"Source 2\n";
	for(i=0;i<v2.size();i++)
		cout<<v2[i]<<"\n";
	cout<<"Source 3\n";
	for(i=0;i<v3.size();i++)
		cout<<v3[i]<<"\n";

	return 0;
}
