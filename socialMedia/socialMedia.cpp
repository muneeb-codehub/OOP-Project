#include "socialMedia.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

// Initialize static member
Date Date::currentDate(15, 11, 2017);

// ==================== Date Class Implementation ====================
Date::Date() : day(1), month(1), year(2017) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

string Date::toString() const {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

int Date::daysSince(const Date& other) const {
    int days1 = year * 365 + month * 30 + day;
    int days2 = other.year * 365 + other.month * 30 + other.day;
    return abs(days1 - days2);
}

// ==================== Activity Class Implementation ====================
Activity::Activity() : type(0), value("") {}

Activity::Activity(int t, const string& val) : type(t), value(val) {}

int Activity::getType() const { return type; }
string Activity::getValue() const { return value; }

void Activity::setActivity(int t, const string& val) {
    type = t;
    value = val;
}

string Activity::toString() const {
    switch (type) {
        case 1: return "feeling " + value;
        case 2: return "thinking about " + value;
        case 3: return "making " + value;
        case 4: return "celebrating " + value;
        default: return "";
    }
}

// ==================== Comment Class Implementation ====================
Comment::Comment(const string& id, const string& txt, SocialEntity* entity)
    : commentID(id), text(txt), commentBy(entity) {}

Comment::~Comment() {}

string Comment::getID() const { return commentID; }
string Comment::getText() const { return text; }
SocialEntity* Comment::getCommentBy() const { return commentBy; }

void Comment::display() const {
    if (commentBy) {
        cout << "\t" << commentBy->getName() << " wrote: \"" << text << "\"\n";
    }
}

// ==================== SocialEntity Class Implementation ====================


SocialEntity::SocialEntity(const string& name, const string& id) 
    : entityID(id), entityName(name) {}

// Add virtual destructor to make SocialEntity polymorphic
SocialEntity::~SocialEntity() {}

string SocialEntity::getID() const { return entityID; }
string SocialEntity::getName() const { return entityName; }

// ==================== User Class Implementation ====================
User::User(const string& name, const string& id) : SocialEntity(name, id) {
    timeline = new Post*[MAX_SIZE];
    friends = new User*[MAX_SIZE];
    likedPages = new Page*[MAX_SIZE];
    timelineSize = 0;
    friendsSize = 0;
    likedPagesSize = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        timeline[i] = nullptr;
        friends[i] = nullptr;
        likedPages[i] = nullptr;
    }
}

// Copy constructor
User::User(const User& other) : SocialEntity(other.entityName, other.entityID) {
    timelineSize = other.timelineSize;
    friendsSize = other.friendsSize;
    likedPagesSize = other.likedPagesSize;
    
    timeline = new Post*[MAX_SIZE];
    friends = new User*[MAX_SIZE];
    likedPages = new Page*[MAX_SIZE];
    
    for (int i = 0; i < timelineSize; i++) timeline[i] = other.timeline[i];
    for (int i = 0; i < friendsSize; i++) friends[i] = other.friends[i];
    for (int i = 0; i < likedPagesSize; i++) likedPages[i] = other.likedPages[i];
}

// Assignment operator
User& User::operator=(const User& other) {
    if (this != &other) {
        delete[] timeline;
        delete[] friends;
        delete[] likedPages;
        
        entityID = other.entityID;
        entityName = other.entityName;
        timelineSize = other.timelineSize;
        friendsSize = other.friendsSize;
        likedPagesSize = other.likedPagesSize;
        
        timeline = new Post*[MAX_SIZE];
        friends = new User*[MAX_SIZE];
        likedPages = new Page*[MAX_SIZE];
        
        for (int i = 0; i < timelineSize; i++) timeline[i] = other.timeline[i];
        for (int i = 0; i < friendsSize; i++) friends[i] = other.friends[i];
        for (int i = 0; i < likedPagesSize; i++) likedPages[i] = other.likedPages[i];
    }
    return *this;
}

User::~User() {
    delete[] timeline;
    delete[] friends;
    delete[] likedPages;
}

int User::getLikedPagesSize() const { return likedPagesSize; }
int User::getFriendsSize() const { return friendsSize; }

void User::addFriend(User* friendUser) {
    if (friendsSize < MAX_SIZE && friendUser != nullptr) {
        friends[friendsSize++] = friendUser;
    }
}

void User::addLikedPage(Page* page) {
    if (likedPagesSize < MAX_SIZE && page != nullptr) {
        likedPages[likedPagesSize++] = page;
    }
}

User** User::getFriends() const { return friends; }
Page** User::getLikedPages() const { return likedPages; }
Post** User::getTimeline() const { return timeline; }
int User::getTimelineSize() const { return timelineSize; }

void User::addPost(Post* post) {
    if (timelineSize < MAX_SIZE && post != nullptr) {
        timeline[timelineSize++] = post;
    }
}

// ==================== Post Class Implementation ====================
Post::Post(const string& content, const string& id, SocialEntity* shared)
    : postID(id), postContent(content), sharedBy(shared) {
    likedBy = new SocialEntity*[MAX_SIZE];
    comments = new Comment*[MAX_SIZE];
    likedBySize = 0;
    commentsSize = 0;
    activity = nullptr;
    for (int i = 0; i < MAX_SIZE; i++) {
        likedBy[i] = nullptr;
        comments[i] = nullptr;
    }
}

// Copy constructor
Post::Post(const Post& other) : postID(other.postID), postContent(other.postContent),
    sharedDate(other.sharedDate), sharedBy(other.sharedBy) {
    likedBySize = other.likedBySize;
    commentsSize = other.commentsSize;
    
    likedBy = new SocialEntity*[MAX_SIZE];
    comments = new Comment*[MAX_SIZE];
    
    for (int i = 0; i < likedBySize; i++) likedBy[i] = other.likedBy[i];
    for (int i = 0; i < commentsSize; i++) comments[i] = other.comments[i];
    
    if (other.activity) {
        activity = new Activity(other.activity->getType(), other.activity->getValue());
    } else {
        activity = nullptr;
    }
}

// Assignment operator
Post& Post::operator=(const Post& other) {
    if (this != &other) {
        delete[] likedBy;
        delete[] comments;
        delete activity;
        
        postID = other.postID;
        postContent = other.postContent;
        sharedDate = other.sharedDate;
        sharedBy = other.sharedBy;
        likedBySize = other.likedBySize;
        commentsSize = other.commentsSize;
        
        likedBy = new SocialEntity*[MAX_SIZE];
        comments = new Comment*[MAX_SIZE];
        
        for (int i = 0; i < likedBySize; i++) likedBy[i] = other.likedBy[i];
        for (int i = 0; i < commentsSize; i++) comments[i] = other.comments[i];
        
        if (other.activity) {
            activity = new Activity(other.activity->getType(), other.activity->getValue());
        } else {
            activity = nullptr;
        }
    }
    return *this;
}

Post::~Post() {
    delete[] likedBy;
    for (int i = 0; i < commentsSize; i++) {
        delete comments[i];
    }
    delete[] comments;
    delete activity;
}

string Post::getID() const { return postID; }
string Post::getContent() const { return postContent; }
Date Post::getSharedDate() const { return sharedDate; }
int Post::getNumLikes() const { return likedBySize; }
SocialEntity* Post::getSharedBy() const { return sharedBy; }
Activity* Post::getActivity() const { return activity; }
int Post::getCommentsSize() const { return commentsSize; }
Comment** Post::getComments() const { return comments; }

void Post::setSharedDate(int day, int month, int year) {
    sharedDate.setDate(day, month, year);
}

void Post::setSharedBy(SocialEntity* entity) {
    sharedBy = entity;
}

void Post::setActivity(Activity* act) {
    activity = act;
}

void Post::addLike(SocialEntity* entity) {
    if (likedBySize < MAX_SIZE && entity != nullptr) {
        likedBy[likedBySize++] = entity;
    }
}

SocialEntity** Post::getLikedBy() const { return likedBy; }

void Post::addComment(Comment* comment) {
    if (commentsSize < MAX_SIZE && comment != nullptr) {
        comments[commentsSize++] = comment;
    }
}

void Post::display() const {
    cout << "--- ";
    if (sharedBy) {
        cout << sharedBy->getName();
        if (activity) {
            cout << " is " << activity->toString();
        }
    }
    cout << "\n\"" << postContent << "\"";
    if (sharedDate.getDay() != 0) {
        cout << " ... (" << sharedDate.toString() << ")";
    }
    cout << "\n";
    
    // Display comments
    for (int i = 0; i < commentsSize; i++) {
        if (comments[i]) {
            comments[i]->display();
        }
    }
    cout << "\n";
}

// ==================== Derived Post Classes ====================
FeelingPost::FeelingPost(const string& content, const string& id, const string& feeling, SocialEntity* shared)
    : Post(content, id, shared) {
    activity = new Activity(1, feeling);
}

void FeelingPost::display() const {
    Post::display();
}

ThinkingPost::ThinkingPost(const string& content, const string& id, const string& thought, SocialEntity* shared)
    : Post(content, id, shared) {
    activity = new Activity(2, thought);
}

void ThinkingPost::display() const {
    Post::display();
}

MakingPost::MakingPost(const string& content, const string& id, const string& making, SocialEntity* shared)
    : Post(content, id, shared) {
    activity = new Activity(3, making);
}

void MakingPost::display() const {
    Post::display();
}

CelebratingPost::CelebratingPost(const string& content, const string& id, const string& occasion, SocialEntity* shared)
    : Post(content, id, shared) {
    activity = new Activity(4, occasion);
}

void CelebratingPost::display() const {
    Post::display();
}

// ==================== Page Class Implementation ====================
Page::Page(const string& name, const string& id) : SocialEntity(name, id) {
    posts = new Post*[MAX_SIZE];
    postsSize = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        posts[i] = nullptr;
    }
}

// Copy constructor
Page::Page(const Page& other) : SocialEntity(other.entityName, other.entityID) {
    postsSize = other.postsSize;
    posts = new Post*[MAX_SIZE];
    for (int i = 0; i < postsSize; i++) posts[i] = other.posts[i];
}

// Assignment operator
Page& Page::operator=(const Page& other) {
    if (this != &other) {
        delete[] posts;
        
        entityID = other.entityID;
        entityName = other.entityName;
        postsSize = other.postsSize;
        
        posts = new Post*[MAX_SIZE];
        for (int i = 0; i < postsSize; i++) posts[i] = other.posts[i];
    }
    return *this;
}

Page::~Page() {
    delete[] posts;
}

void Page::addPost(Post* post) {
    if (postsSize < MAX_SIZE && post != nullptr) {
        posts[postsSize++] = post;
    }
}

Post** Page::getPosts() const { return posts; }
int Page::getPostsSize() const { return postsSize; }

// ==================== Helper Functions ====================
User* findUserByID(const string& userID, User* users[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (users[i] && users[i]->getID() == userID) {
            return users[i];
        }
    }
    return nullptr;
}

Page* findPageByID(const string& pageID, Page* pages[], int pageCount) {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] && pages[i]->getID() == pageID) {
            return pages[i];
        }
    }
    return nullptr;
}

Post* findPostByID(const string& postID, Post* posts[], int postCount) {
    for (int i = 0; i < postCount; i++) {
        if (posts[i] && posts[i]->getID() == postID) {
            return posts[i];
        }
    }
    return nullptr;
}

// ==================== File I/O Functions ====================
void loadUsersFromFile(User* users[], int& userCount) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open users.txt\n";
        return;
    }
    
    userCount = 0;
    string line;
    
    while (getline(file, line) && userCount < 20) {
        if (line.empty()) continue;
        
        string userID = line;
        getline(file, line);
        string userName = line;
        
        users[userCount] = new User(userName, userID);
        
        // Read friend IDs
        getline(file, line);
        if (!line.empty() && line != "-1") {
            stringstream ss(line);
            string friendID;
            while (getline(ss, friendID, ',')) {
                // Will link friends after all users are loaded
            }
        }
        
        // Read liked page IDs
        getline(file, line);
        if (!line.empty() && line != "-1") {
            // Will link pages after pages are loaded
        }
        
        userCount++;
    }
    
    file.close();
}

void loadPagesFromFile(Page* pages[], int& pageCount) {
    ifstream file("pages.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open pages.txt\n";
        return;
    }
    
    pageCount = 0;
    string line;
    
    while (getline(file, line) && pageCount < 20) {
        if (line.empty()) continue;
        
        string pageID = line;
        getline(file, line);
        string pageTitle = line;
        
        pages[pageCount] = new Page(pageTitle, pageID);
        pageCount++;
    }
    
    file.close();
}

void loadPostsFromFile(Post* posts[], int& postCount, User* users[], Page* pages[], int userCount, int pageCount) {
    ifstream file("posts.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open posts.txt\n";
        return;
    }
    
    postCount = 0;
    string line;
    
    while (getline(file, line) && postCount < 50) {
        if (line.empty()) continue;
        
        string postID = line;
        
        // Date
        getline(file, line);
        int day, month, year;
        sscanf(line.c_str(), "%d-%d-%d", &day, &month, &year);
        
        // Content
        getline(file, line);
        string content = line;
        
        // Liked by
        getline(file, line);
        
        // Comments
        getline(file, line);
        
        // Shared by
        getline(file, line);
        SocialEntity* sharedBy = nullptr;
        if (!line.empty() && line != "-1") {
            if (line[0] == 'u') {
                sharedBy = findUserByID(line, users, userCount);
            } else if (line[0] == 'p') {
                sharedBy = findPageByID(line, pages, pageCount);
            }
        }
        
        // Activity
        getline(file, line);
        Post* post = nullptr;
        
        if (!line.empty() && line != "-1") {
            int type;
            string value;
            size_t dashPos = line.find('-');
            if (dashPos != string::npos) {
                type = stoi(line.substr(0, dashPos));
                value = line.substr(dashPos + 1);
                
                switch (type) {
                    case 1:
                        post = new FeelingPost(content, postID, value, sharedBy);
                        break;
                    case 2:
                        post = new ThinkingPost(content, postID, value, sharedBy);
                        break;
                    case 3:
                        post = new MakingPost(content, postID, value, sharedBy);
                        break;
                    case 4:
                        post = new CelebratingPost(content, postID, value, sharedBy);
                        break;
                    default:
                        post = new Post(content, postID, sharedBy);
                }
            }
        } else {
            post = new Post(content, postID, sharedBy);
        }
        
        if (post) {
            post->setSharedDate(day, month, year);
            posts[postCount++] = post;
            
            // Add post to entity's timeline
            if (sharedBy) {
                User* user = dynamic_cast<User*>(sharedBy);
                if (user) {
                    user->addPost(post);
                } else {
                    Page* page = dynamic_cast<Page*>(sharedBy);
                    if (page) {
                        page->addPost(post);
                    }
                }
            }
        }
    }
    
    file.close();
    
    // Re-read to add likes and comments
    file.open("posts.txt");
    int idx = 0;
    while (getline(file, line) && idx < postCount) {
        if (line.empty()) continue;
        
        getline(file, line); // skip postID
        getline(file, line); // skip date
        getline(file, line); // skip content
        
        // Liked by
        getline(file, line);
        if (!line.empty() && line != "-1") {
            stringstream ss(line);
            string entityID;
            while (getline(ss, entityID, ',')) {
                SocialEntity* entity = nullptr;
                if (entityID[0] == 'u') {
                    entity = findUserByID(entityID, users, userCount);
                } else if (entityID[0] == 'p') {
                    entity = findPageByID(entityID, pages, pageCount);
                }
                if (entity) {
                    posts[idx]->addLike(entity);
                }
            }
        }
        
        // Comments
        getline(file, line);
        if (!line.empty() && line != "-1") {
            stringstream ss(line);
            string commentStr;
            int commentIdx = 0;
            while (getline(ss, commentStr, ',')) {
                size_t dashPos = commentStr.find('-');
                if (dashPos != string::npos) {
                    string commenterID = commentStr.substr(0, dashPos);
                    string commentText = commentStr.substr(dashPos + 1);
                    
                    SocialEntity* commenter = nullptr;
                    if (commenterID[0] == 'u') {
                        commenter = findUserByID(commenterID, users, userCount);
                    } else if (commenterID[0] == 'p') {
                        commenter = findPageByID(commenterID, pages, pageCount);
                    }
                    
                    if (commenter) {
                        Comment* comment = new Comment("c" + to_string(commentIdx++), commentText, commenter);
                        posts[idx]->addComment(comment);
                    }
                }
            }
        }
        
        getline(file, line); // skip shared by
        getline(file, line); // skip activity
        
        idx++;
    }
    
    file.close();
}

// ==================== Application Functions ====================
User* setCurrentUser(const string& userID, User* users[], int userCount) {
    User* user = findUserByID(userID, users, userCount);
    if (user) {
        cout << "Command: Set current user \"" << userID << "\"\n";
        cout << user->getName() << " successfully set as Current User\n";
        cout << "\nCommand:\nSystem Date: " << Date::currentDate.toString() << "\n";
    }
    return user;
}

void viewFriendList(User* user) {
    if (!user) return;
    
    cout << "\nCommand: View Friend List\n";
    cout << "-----------------------------------\n";
    cout << user->getName() << " - Friend List\n";
    
    User** friends = user->getFriends();
    for (int i = 0; i < user->getFriendsSize(); i++) {
        if (friends[i]) {
            cout << friends[i]->getID() << " - " << friends[i]->getName() << "\n";
        }
    }
    cout << "-----------------------------------\n";
}

void viewLikedPages(User* user) {
    if (!user) return;
    
    cout << "\nCommand: View Liked Pages\n";
    cout << "-----------------------------------\n";
    cout << user->getName() << " - Liked Pages\n";
    
    Page** pages = user->getLikedPages();
    for (int i = 0; i < user->getLikedPagesSize(); i++) {
        if (pages[i]) {
            cout << pages[i]->getID() << " - " << pages[i]->getName() << "\n";
        }
    }
    cout << "-----------------------------------\n";
}

void viewHome(User* currentUser) {
    if (!currentUser) return;
    
    cout << "\nCommand: View Home\n";
    cout << "-----------------------------------\n";
    cout << currentUser->getName() << " - Home Page\n\n";
    
    // Show friends' posts from last 2 days
    User** friends = currentUser->getFriends();
    for (int i = 0; i < currentUser->getFriendsSize(); i++) {
        if (friends[i]) {
            Post** timeline = friends[i]->getTimeline();
            for (int j = 0; j < friends[i]->getTimelineSize(); j++) {
                if (timeline[j]) {
                    int daysDiff = Date::currentDate.daysSince(timeline[j]->getSharedDate());
                    if (daysDiff <= 1) {
                        timeline[j]->display();
                    }
                }
            }
        }
    }
    
    // Show liked pages' posts from last 2 days
    Page** pages = currentUser->getLikedPages();
    for (int i = 0; i < currentUser->getLikedPagesSize(); i++) {
        if (pages[i]) {
            Post** pagePosts = pages[i]->getPosts();
            for (int j = 0; j < pages[i]->getPostsSize(); j++) {
                if (pagePosts[j]) {
                    int daysDiff = Date::currentDate.daysSince(pagePosts[j]->getSharedDate());
                    if (daysDiff <= 1) {
                        pagePosts[j]->display();
                    }
                }
            }
        }
    }
    
    cout << "-----------------------------------\n";
}

void viewUserTimeline(const User* user) {
    if (!user) return;
    
    cout << "\nCommand: View TimeLine\n";
    cout << "-----------------------------------\n";
    cout << user->getName() << " - Time Line\n\n";
    
    Post** timeline = user->getTimeline();
    for (int i = 0; i < user->getTimelineSize(); i++) {
        if (timeline[i]) {
            timeline[i]->display();
        }
    }
    
    cout << "-----------------------------------\n";
}

void viewPostLikes(const Post* post) {
    if (!post) return;
    
    cout << "\nCommand: ViewLikedList(" << post->getID() << ")\n";
    cout << "Post Liked By:\n";
    
    SocialEntity** likedBy = post->getLikedBy();
    for (int i = 0; i < post->getNumLikes(); i++) {
        if (likedBy[i]) {
            cout << likedBy[i]->getID() << " - " << likedBy[i]->getName() << "\n";
        }
    }
    cout << "-----------------------------------\n";
}

void likePost(User* currentUser, Post* post) {
    if (!currentUser || !post) return;
    
    cout << "\nCommand: LikePost(" << post->getID() << ")\n";
    post->addLike(currentUser);
}

void commentOnPost(Post* post, const string& commentText, User* currentUser) {
    if (!post || !currentUser) return;
    
    cout << "\nCommand: PostComment(" << post->getID() << ", " << commentText << ")\n";
    Comment* comment = new Comment("c" + to_string(post->getCommentsSize()), commentText, currentUser);
    post->addComment(comment);
}

void viewPost(const Post* post) {
    if (!post) return;
    
    cout << "\nCommand: ViewPost(" << post->getID() << ")\n";
    cout << "-----------------------------------\n";
    post->display();
    cout << "-----------------------------------\n";
}

void sharePost(User* currentUser, Post* originalPost) {
    if (!currentUser || !originalPost) return;
    
    cout << "\nCommand: SharePost(" << originalPost->getID() << ")\n";
    
    // Create new post with shared content
    string sharedContent = originalPost->getSharedBy()->getName();
    if (originalPost->getActivity()) {
        sharedContent += " is " + originalPost->getActivity()->toString() + ".";
    }
    
    Post* sharedPost = new Post(sharedContent, originalPost->getID() + "_shared", currentUser);
    sharedPost->setSharedDate(Date::currentDate.getDay(), Date::currentDate.getMonth(), Date::currentDate.getYear());
    currentUser->addPost(sharedPost);
}

void viewPage(Page* page) {
    if (!page) return;
    
    cout << "\nCommand: ViewPage(" << page->getID() << ")\n";
    cout << "-----------------------------------\n";
    cout << page->getName() << "\n\n";
    
    Post** posts = page->getPosts();
    for (int i = 0; i < page->getPostsSize(); i++) {
        if (posts[i]) {
            posts[i]->display();
        }
    }
    
    cout << "-----------------------------------\n";
}

void search(const string& keyword, User* users[], Page* pages[], Post* posts[], int userCount, int pageCount, int postCount) {
    cout << "\nCommand: Search(\"" << keyword << "\")\n";
    
    bool foundUsers = false, foundPosts = false, foundPages = false;
    
    // Search users
    for (int i = 0; i < userCount; i++) {
        if (users[i] && users[i]->getName().find(keyword) != string::npos) {
            if (!foundUsers) {
                cout << "Users:\n";
                foundUsers = true;
            }
            cout << "--- " << users[i]->getID() << " - " << users[i]->getName() << "\n";
        }
    }
    
    // Search posts
    for (int i = 0; i < postCount; i++) {
        if (posts[i]) {
            bool match = posts[i]->getContent().find(keyword) != string::npos;
            if (posts[i]->getActivity()) {
                match = match || posts[i]->getActivity()->getValue().find(keyword) != string::npos;
            }
            
            if (match) {
                if (!foundPosts) {
                    cout << "Posts:\n";
                    foundPosts = true;
                }
                cout << "--- " << posts[i]->getID() << " - ";
                if (posts[i]->getSharedBy()) {
                    cout << posts[i]->getSharedBy()->getName();
                    if (posts[i]->getActivity()) {
                        cout << " is " << posts[i]->getActivity()->toString();
                    }
                }
                cout << "\n\"" << posts[i]->getContent() << "\" ... (" 
                     << posts[i]->getSharedDate().toString() << ")\n";
            }
        }
    }
    
    // Search pages
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] && pages[i]->getName().find(keyword) != string::npos) {
            if (!foundPages) {
                cout << "Pages:\n";
                foundPages = true;
            }
            cout << "--- " << pages[i]->getID() << " - " << pages[i]->getName() << "\n";
        }
    }
    
    cout << "-----------------------------------\n";
}
