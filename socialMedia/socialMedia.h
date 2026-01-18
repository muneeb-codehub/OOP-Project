#ifndef SOCIAL_MEDIA_H
#define SOCIAL_MEDIA_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// Forward declarations
class Post;
class Page;
class User;
class Date;
class Activity;
class Comment;

// Date Class
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);
    
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    void setDate(int d, int m, int y);
    string toString() const;
    int daysSince(const Date& other) const;
    static Date currentDate;
};

// Activity Class
class Activity {
private:
    int type;  // 1=feeling, 2=thinking, 3=making, 4=celebrating
    string value;

public:
    Activity();
    Activity(int t, const string& val);
    
    int getType() const;
    string getValue() const;
    void setActivity(int t, const string& val);
    string toString() const;
};

// Comment Class
class Comment {
private:
    string commentID;
    string text;
    SocialEntity* commentBy;

public:
    Comment(const string& id, const string& txt, SocialEntity* entity);
    ~Comment();
    
    string getID() const;
    string getText() const;
    SocialEntity* getCommentBy() const;
    void display() const;
};

// Main Class SocialEntity
class SocialEntity {
protected:
    string entityID;
    string entityName;

public:
    SocialEntity(const string& name, const string& id);
    virtual ~SocialEntity();

    string getID() const;
    string getName() const;
};

// Derived from SocialEntity/ User Class
class User : public SocialEntity {
private:
    Post** timeline;
    User** friends;
    Page** likedPages;
    int timelineSize;
    int friendsSize;
    int likedPagesSize;
    static const int MAX_SIZE = 10;

public:
    User(const string& name, const string& id);
    User(const User& other);  // Copy constructor
    User& operator=(const User& other);  // Assignment operator

    int getLikedPagesSize() const;
    ~User();

    int getFriendsSize() const;
    void addFriend(User* friendUser);
    void addLikedPage(Page* page);

    User** getFriends() const;
    Page** getLikedPages() const;
    Post** getTimeline() const;
    int getTimelineSize() const;

    void addPost(Post* post);
    void viewHome() const;
    void viewTimeline() const;
    void viewFriendList() const;
    void viewPage(Page* page) const;
    void search(const string& keyword, User* users[], Page* pages[]) const;
};

// Post Class
// Base class Post
class Post {
protected:
    string postID;
    string postContent;
    Date sharedDate;
    SocialEntity* sharedBy;
    SocialEntity** likedBy;
    Comment** comments;
    int likedBySize;
    int commentsSize;
    Activity* activity;
    static const int MAX_SIZE = 10;

public:
    Post(const string& content, const string& id, SocialEntity* shared = nullptr);
    Post(const Post& other);  // Copy constructor
    Post& operator=(const Post& other);  // Assignment operator

    virtual ~Post();  // Make the destructor virtual for proper cleanup in derived classes

    string getID() const;
    string getContent() const;
    Date getSharedDate() const;
    int getNumLikes() const;
    SocialEntity* getSharedBy() const;
    Activity* getActivity() const;

    int getCommentsSize() const;
    Comment** getComments() const;

    void setSharedDate(int day, int month, int year);
    void setSharedBy(SocialEntity* entity);
    void setActivity(Activity* act);
    
    void addLike(SocialEntity* entity);
    SocialEntity** getLikedBy() const;

    void addComment(Comment* comment);
    virtual void display() const;  // Make a virtual display function for polymorphic behavior
};

// Derived class FeelingPost
class FeelingPost : public Post {
public:
    FeelingPost(const string& content, const string& id, const string& feeling, SocialEntity* shared = nullptr);
    void display() const override;
};

// Derived class ThinkingPost
class ThinkingPost : public Post {
public:
    ThinkingPost(const string& content, const string& id, const string& thought, SocialEntity* shared = nullptr);
    void display() const override;
};

// Derived class MakingPost
class MakingPost : public Post {
public:
    MakingPost(const string& content, const string& id, const string& making, SocialEntity* shared = nullptr);
    void display() const override;
};

// Derived class CelebratingPost
class CelebratingPost : public Post {
public:
    CelebratingPost(const string& content, const string& id, const string& occasion, SocialEntity* shared = nullptr);
    void display() const override;
};

// Derived from SocialEntity/ Page Class
class Page : public SocialEntity {
private:
    Post** posts;
    int postsSize;
    static const int MAX_SIZE = 10;

public:
    Page(const string& name, const string& id);
    Page(const Page& other);  // Copy constructor
    Page& operator=(const Page& other);  // Assignment operator

    ~Page();

    void addPost(Post* post);
    Post** getPosts() const;
    int getPostsSize() const;
};

// Function prototypes
void loadUsersFromFile(User* users[], int& userCount);
void loadPagesFromFile(Page* pages[], int& pageCount);
void loadPostsFromFile(Post* posts[], int& postCount, User* users[], Page* pages[], int userCount, int pageCount);
void savePostsToFile(const Post* posts[], int size);

User* setCurrentUser(const string& userID, User* users[], int userCount);
void viewHome(User* currentUser);
void likePost(User* currentUser, Post* post);
void viewPostLikes(const Post* post);
void commentOnPost(Post* post, const string& commentText, User* currentUser);
void viewUserTimeline(const User* user);
void viewFriendList(User* user);
void viewPage(Page* page);
void viewLikedPages(User* user);
void search(const string& keyword, User* users[], Page* pages[], Post* posts[], int userCount, int pageCount, int postCount);
void viewPost(const Post* post);
void sharePost(User* currentUser, Post* originalPost);

Post* findPostByID(const string& postID, Post* posts[], int postCount);
User* findUserByID(const string& userID, User* users[], int userCount);
Page* findPageByID(const string& pageID, Page* pages[], int pageCount);

#endif  // SOCIAL_MEDIA_H