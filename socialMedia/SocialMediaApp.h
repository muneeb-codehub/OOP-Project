#include "socialMedia.h"

class SocialNetworkApp {
public:
    static void Run() {
        // Arrays for users, pages, and posts
        User* users[20];
        Page* pages[20];
        Post* posts[50];
        
        int userCount = 0;
        int pageCount = 0;
        int postCount = 0;
        
        // Load data from files
        loadUsersFromFile(users, userCount);
        loadPagesFromFile(pages, pageCount);
        loadPostsFromFile(posts, postCount, users, pages, userCount, pageCount);
        
        // Link friends and liked pages
        if (userCount > 0) {
            // u7's friends: u3, u11, u12
            User* u7 = findUserByID("u7", users, userCount);
            User* u3 = findUserByID("u3", users, userCount);
            User* u11 = findUserByID("u11", users, userCount);
            User* u12 = findUserByID("u12", users, userCount);
            
            if (u7) {
                if (u3) u7->addFriend(u3);
                if (u11) u7->addFriend(u11);
                if (u12) u7->addFriend(u12);
                
                // u7's liked pages: p1, p2, p5, p9
                Page* p1 = findPageByID("p1", pages, pageCount);
                Page* p2 = findPageByID("p2", pages, pageCount);
                Page* p5 = findPageByID("p5", pages, pageCount);
                Page* p9 = findPageByID("p9", pages, pageCount);
                
                if (p1) u7->addLikedPage(p1);
                if (p2) u7->addLikedPage(p2);
                if (p5) u7->addLikedPage(p5);
                if (p9) u7->addLikedPage(p9);
            }
            
            // u3's friends
            if (u3) {
                if (u11) u3->addFriend(u11);
                if (u12) u3->addFriend(u12);
            }
            
            // u11's friend
            if (u11 && u7) {
                u11->addFriend(u7);
            }
            
            // u12's friend
            if (u12 && u7) {
                u12->addFriend(u7);
            }
        }
        
        // ===== Execute the Sample Run =====
        
        // Set current system date
        Date::currentDate.setDate(15, 11, 2017);
        
        // Set current user u7
        User* currentUser = setCurrentUser("u7", users, userCount);
        
        if (currentUser) {
            // View Friend List
            viewFriendList(currentUser);
            
            // View Liked Pages
            viewLikedPages(currentUser);
            
            // View Home
            viewHome(currentUser);
            
            // View Timeline
            viewUserTimeline(currentUser);
            
            // View Liked List for post5
            Post* post5 = findPostByID("post5", posts, postCount);
            if (post5) {
                viewPostLikes(post5);
                
                // Like post5
                likePost(currentUser, post5);
                
                // View updated liked list
                viewPostLikes(post5);
            }
            
            // Post comment on post4
            Post* post4 = findPostByID("post4", posts, postCount);
            if (post4) {
                commentOnPost(post4, "Good Luck for your Result", currentUser);
                viewPost(post4);
            }
            
            // Post comment on post8
            Post* post8 = findPostByID("post8", posts, postCount);
            if (post8) {
                commentOnPost(post8, "Thanks for the wishes", currentUser);
                viewPost(post8);
            }
            
            // Share post5
            if (post5) {
                sharePost(currentUser, post5);
                viewUserTimeline(currentUser);
            }
            
            // View page p1
            Page* p1 = findPageByID("p1", pages, pageCount);
            if (p1) {
                viewPage(p1);
            }
            
            // Search for "Birthday"
            search("Birthday", users, pages, posts, userCount, pageCount, postCount);
            
            // Search for "Ali"
            search("Ali", users, pages, posts, userCount, pageCount, postCount);
        }
        
        // Cleanup
        for (int i = 0; i < userCount; i++) {
            delete users[i];
        }
        
        for (int i = 0; i < pageCount; i++) {
            delete pages[i];
        }
        
        for (int i = 0; i < postCount; i++) {
            delete posts[i];
        }
    }
};
