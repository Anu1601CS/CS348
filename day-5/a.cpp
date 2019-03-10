#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define INF 1000000000
#define fastIO                   \
	ios::sync_with_stdio(false); \
	cout.tie(0);                 \
	cin.tie(0);
#define endl '\n'
#define foreach(v, c) for (typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define all(a) a.begin(), a.end()
#define in(a, b) ((b).find(a) != (b).end())
#define fill(a, v) memset(a, v, sizeof a)
#define sz(a) ((int)(a.size()))
#define mp make_pair
#define pb push_back

int n;
double packet_size;
struct source
{
	double bandwidth;
	double mean_sending_rate;
};

source s[1000];
double max_s[1000];
double max_s1;
double switch_proc_delay;

struct packet
{
	int src_id;
	lli p_id;
};

struct event
{
	double occ_time;
	packet p;
};

class compare
{
  public:
	bool operator()(event e1, event e2)
	{
		return e1.occ_time > e2.occ_time;
	}
};

priority_queue<event, vector<event>, compare> global_queue;
double time_to_run;
double bandwidth_sw_src;
double tot_packets[1000];
double tot_time[1000];
lli switch_queue_size;
lli cwnd[1000];
lli last_red_time[1000];
lli last_red_size[1000];
lli RTT[1000];
void AIMD1(int j)
{
	cwnd[j] /= 5;
}

void AIMD2(int j)
{
	cwnd[j] += 1;
}

void CUBIC1(int j)
{
	cwnd[j] = 1;
}

void CUBIC2(int j, int i)
{
	cwnd[j] = 5 * (i - last_red_time[j]) * (i - last_red_time[j]) * (i - last_red_time[j]) + last_red_size[j];
}

int main()
{
	fastIO
			cout
		<< "Enter the packet size" << endl;
	cin >> packet_size;
	cout << "Enter the switch queue size" << endl;
	cin >> switch_queue_size;
	cout << "Enter the number of sources" << endl;
	cin >> n;
	cout << "Enter the bandwidth and RTT of each source" << endl;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i].bandwidth >> RTT[i];
	}
	cout << "Enter the bandwidth from switch to sink" << endl;
	cin >> bandwidth_sw_src;
	//for(float j = 1; j <= 200; j = j + 1){
	max_s1 = 0;
	//s[2].mean_sending_rate = j*2;
	//s[3].mean_sending_rate = j + 100;
	//s[1].mean_sending_rate = j;
	for (int i = 1; i <= n; i++)
	{
		max_s[i] = 0;
		tot_packets[i] = 0;
		tot_time[i] = 0;
	}
	/*for(int i = 1; i <= n; i++){
		double t = 1/s[i].mean_sending_rate;
		double temp = t;
		t = 0;
		while(1){
			double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			temp = -log(r)/s[i].mean_sending_rate;
			event e;
			e.event_type = 1;
			e.occ_time = t;
			e.p.src_id = i;
			e.p.time = t;
			tot_packets[i]++;
			global_queue.push(e);
			t += temp;
			if(t >= time_to_run)break;
		}
	}
	lli num = 0;
	lli dropped1, dropped2, dropped3;
	dropped1 = dropped2 = dropped3 = 0;
	while(!global_queue.empty()){
		event e = global_queue.top();
		global_queue.pop();
		//cout<<e.event_type<<" "<<e.occ_time<<" "<<max_s[e.p.src_id]<<endl;
		if(e.event_type == 1){
			if(num > switch_queue_size){
				if(e.p.src_id == 1)dropped1++;
				else if(e.p.src_id == 2)dropped2++;
				else dropped3++;
				continue;
			}
			e.event_type = 2;
			if(e.p.time <= max_s[e.p.src_id]){
				e.occ_time = max_s[e.p.src_id] + packet_size/s[e.p.src_id].bandwidth;
			}
			else{
				e.occ_time = e.p.time + packet_size/s[e.p.src_id].bandwidth;
			}
			max_s[e.p.src_id] = e.occ_time;
			global_queue.push(e);
			num++;
		}
		else if(e.event_type == 2){
			num--;
			if(e.occ_time <= max_s1){
				double completion_time = max_s1 + packet_size/bandwidth_sw_src;
				int x = e.p.src_id;
				tot_time[x] += completion_time - e.p.time;
				max_s1 = completion_time;
				//cout<<completion_time - e.p.time<<endl;
			}
			else{
				double completion_time = e.occ_time + packet_size/bandwidth_sw_src;
				tot_time[e.p.src_id] += completion_time - e.p.time;
				max_s1 = completion_time;
				//cout<<completion_time - e.p.time<<endl;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		cout<<"The average delay of source "<<i<<": "<<tot_time[i]/tot_packets[i]<<endl;
	}*/
	lli last_ack[1000];
	lli last_sent[1000];
	lli num[1000];
	int resend[1000];
	for (int i = 1; i <= 1000; i++)
	{
		cwnd[i] = 1;
		last_sent[i] = 0;
		last_ack[i] = 0;
		resend[i] = 0;
		last_red_time[i] = 0;
		last_red_size[i] = 0;
		num[i] = 0;
	}
	for (int i = 1; i <= 1000; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (resend[j])
			{
				last_sent[j] = last_ack[j];
				resend[j] = 0;
			}
			if (last_sent[j] - last_ack[j] < cwnd[j])
			{
				event e;
				e.occ_time = i + packet_size / s[j].bandwidth + RTT[j] / 2;
				e.p.p_id = last_sent[j] + 1;
				last_sent[j]++;
				e.p.src_id = j;
				if (global_queue.size() < switch_queue_size)
				{
					global_queue.push(e);
				}
				else
				{
					last_red_time[j] = i;
					last_red_size[j] = cwnd[j];
					cwnd[i] = 1;
				}
			}
		}
		event e = global_queue.top();
		while (e.occ_time + RTT[e.p.src_id] / 2 <= i)
		{
			global_queue.pop();
			if (e.p.p_id != last_ack[e.p.src_id] + 1)
			{
				if (num[e.p.src_id] == 3)
				{
					resend[e.p.src_id] = 1;
					cwnd[e.p.src_id] = cwnd[e.p.src_id] / 2;
					num[e.p.src_id] = 0;
				}
				else
					num[e.p.src_id]++;
			}
			else
			{
				last_ack[e.p.src_id]++;
				AIMD2(e.p.src_id);
				//CUBIC2(j, i);
			}
			if (global_queue.size() == 0)
			{
				break;
			}
			e = global_queue.top();
		}
	}
	cout << last_ack[1] << " " << last_ack[2] << endl;
	//cout<<fixed<<tot_time[3]/tot_packets[3]<<endl;
	//cout<<fixed<<dropped1/time_to_run<<endl;
	//}
}
