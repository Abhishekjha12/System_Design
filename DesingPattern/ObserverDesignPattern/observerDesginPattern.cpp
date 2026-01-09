#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class ISubscriber{
public:
    virtual void update()=0;
    virtual ~ISubscriber(){} //virtual destrcutor for interface
};

//Abstract Observable Interface: a YouTube channel interface
class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber)=0;
    virtual void unsubscribe(ISubscriber* subscriber)=0;
    virtual void notifySubscribers()=0;
    virtual ~IChannel(){}
};

//Concrete Subject: A Youtube channel that observers can subscribe to
class Channel : public IChannel{
private:
    vector<ISubscriber*> subscribers;
    string name;
    string latestVideo;

public:
    Channel(const string &name){
        this->name = name;
    }
    
    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber* subscriber) override{
        if(find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()){
            subscribers.push_back(subscriber);
        }
    }

   //Remove a subscriber if present
   void unsubscribe(ISubscriber* subscriber)override{
    auto it = find(subscribers.begin(), subscribers.end(), subscriber);
    if(it!= subscribers.end()){
        subscribers.erase(it);
    }
   }

   // Notify all subscribers of the latest video
   void notifySubscribers()override{
    for(ISubscriber* sub : subscribers){
        sub->update();
    }
   }

   //Upload a new video and notify all subscriber
   void uploadVideo(const string title){
    latestVideo = title;
    cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
    notifySubscribers();
   }

   //Read video data
   string getVideoData(){
    return "\nCheckout our new video : " + latestVideo + "\n";
   }
};

//Concrete Observer : represent a subscriber to the channel
class Subscriber : public ISubscriber{
private:
    string name;
    Channel* channel;
public:
    Subscriber(const string& name, Channel* channel){
        this->name = name;
        this->channel = channel;
    }

    // Called by Channel ; prints notification message
    void update() override{
        cout<<"Hey "<< name << "," << this->channel->getVideoData();
    }
};

int main(){
    Channel* channel = new Channel("CoderArmy");

    Subscriber*s1 = new Subscriber("Abhi",channel);
    Subscriber*s2= new Subscriber("Tannu",channel);

    // Tanu and abhi subscribe to CoderArmy
    channel->subscribe(s1);
    channel->subscribe(s2);

    //Upload a vide : both abhi and tannu are notified
    channel->uploadVideo("Observer Pattern Tutorial");

    //Tannu Unsubscribe : abhi remain subscribed
    channel->unsubscribe(s1);

    //upload another video: only Tarun is notified
    channel->uploadVideo("Decorator Pattern tutorial");

    return 0;
     
}