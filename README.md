# Social Media Application - OOP Project

A C++ console-based social media application that simulates Facebook-like functionality using Object-Oriented Programming concepts.

## Author
**Muneeb Arif**  
Email: muneebarif226@gmail.com

## Project Overview

This project demonstrates a social media platform with users, pages, posts, comments, and likes functionality. It implements core OOP concepts including inheritance, polymorphism, encapsulation, and dynamic memory management.

## Features

- **User Management**: Create users with friends and liked pages
- **Page Management**: Business/interest pages that users can follow
- **Post Types**: Regular posts, feeling posts, thinking posts, making posts, and celebrating posts
- **Social Interactions**: Like posts, comment on posts, share posts
- **Timeline Views**: User timelines, home page with recent posts
- **Search Functionality**: Search for users, pages, and posts by keywords
- **Date-Based Filtering**: Display posts from the last 2 days on home page

## Technical Implementation

### Classes
- `Date` - Manages dates and calculates days between dates
- `Activity` - Represents post activities (feeling, thinking, making, celebrating)
- `Comment` - Stores comment information
- `SocialEntity` - Base class for User and Page (polymorphic)
- `User` - Derived from SocialEntity, manages user data
- `Page` - Derived from SocialEntity, manages page data
- `Post` - Base class for different post types
- `FeelingPost`, `ThinkingPost`, `MakingPost`, `CelebratingPost` - Derived post types

### Key OOP Concepts Demonstrated
- **Inheritance**: User and Page inherit from SocialEntity
- **Polymorphism**: Virtual functions for dynamic_cast and display methods
- **Encapsulation**: Private/protected members with public interfaces
- **Operator Overloading**: Copy constructors and assignment operators
- **Dynamic Memory Management**: Pointers, arrays, new/delete

## File Structure

```
socialMedia/
├── main.cpp                 # Entry point
├── socialMedia.h            # Header file with class declarations
├── socialMedia.cpp          # Implementation of all classes
├── SocialMediaApp.h         # Application logic and sample run
├── users.txt                # User data
├── pages.txt                # Page data
├── posts.txt                # Post data
└── README.md                # This file
```

## Data Files Format

### users.txt
```
<UserID>
<UserName>
<FriendIDs> (comma-separated or -1)
<LikedPageIDs> (comma-separated or -1)
```

### pages.txt
```
<PageID>
<PageTitle>
```

### posts.txt
```
<PostID>
<Day-Month-Year>
<Content>
<LikedBy> (comma-separated or -1)
<Comments> (format: userID-text, comma-separated or -1)
<SharedBy> (userID or pageID)
<Activity> (type-value or -1)
```

## How to Compile and Run

### Using Visual Studio
1. Open `socialMedia.sln`
2. Build the solution (Ctrl+Shift+B)
3. Run (F5 or Ctrl+F5)

### Using g++
```bash
g++ main.cpp socialMedia.cpp -o socialMedia
./socialMedia
```

## Expected Output

### 1. Set Current User
```
Command: Set current user "u7"
Shahem Riaz successfully set as Current User

Command:
System Date: 15/11/2017
```

### 2. View Friend List
```
Command: View Friend List
-----------------------------------
Shahem Riaz - Friend List
u3 - Muneeb Arif
u11 - Ahsan Saeed
u12 - Ali Chapri
-----------------------------------
```

### 3. View Liked Pages
```
Command: View Liked Pages
-----------------------------------
Shahem Riaz - Liked Pages
p1 - Food Fusion
p2 - Al Jazeera English
p5 - Rumi Quotes
p9 - BBC News
-----------------------------------
```

### 4. View Home (Recent Posts)
```
Command: View Home
-----------------------------------
Shahem Riaz - Home Page

--- Food Fusion is making Kashmiri Chai (Pink Tea)
"Try this at home..."
 ... (14/11/2017)
	Food Fusion wrote: "Followers please try this recipe and give your feedback"
	Abdullah Farooq wrote: "Yummy"
	Ahsan Saeed wrote: "One pink tea for me"

--- Ahsan Saeed
"Waiting for Weekend"
 ... (15/11/2017)
	Saad Ali wrote: "Any plans for Get Together?"
	Shahem Riaz wrote: "Yes BBQ"
	Nimra Batool wrote: "Lunch Buffet please"

--- Al Jazeera English
"Oil drilling in Alaska's indigenous communities is on the table again."
 ... (15/11/2017)

--- Rumi Quotes
"Be free of possessing things - Rumi"
 ... (15/11/2017)
	Ali Chapri wrote: "Rumi is great"

-----------------------------------
```

### 5. View Timeline
```
Command: View TimeLine
-----------------------------------
Shahem Riaz - Time Line

--- Shahem Riaz is celebrating a birthday
"Happy Birthday to my dear Mom"
 ... (14/11/2017)
	Muneeb Arif wrote: "Happy Birthday Aunty"

--- Shahem Riaz is celebrating a birthday
"Happy Birthday to my dear Father"
 ... (14/10/2017)
	Ahsan Saeed wrote: "Happy Birthday Uncle"

-----------------------------------
```

### 6. View Post Likes
```
Command: ViewLikedList(post5)
Post Liked By:
u2 - Abdullah Farooq
p1 - Food Fusion
u3 - Muneeb Arif
u4 - Burhan Tahir
-----------------------------------
```

### 7. Like Post
```
Command: LikePost(post5)

Command: ViewLikedList(post5)
Post Liked By:
u2 - Abdullah Farooq
p1 - Food Fusion
u3 - Muneeb Arif
u4 - Burhan Tahir
u7 - Shahem Riaz
-----------------------------------
```

### 8. Post Comment
```
Command: PostComment(post4, Good Luck for your Result)

Command: ViewPost(post4)
-----------------------------------
--- Ali Chapri
"Waiting for Result"
 ... (15/11/2017)
	Shahem Riaz wrote: "Good Luck for your Result"

-----------------------------------
```

### 9. Share Post
```
Command: SharePost(post5)
```

### 10. View Page
```
Command: ViewPage(p1)
-----------------------------------
Food Fusion

--- Food Fusion is making Kashmiri Chai (Pink Tea)
"Try this at home..."
 ... (14/11/2017)
	Food Fusion wrote: "Followers please try this recipe and give your feedback"
	Abdullah Farooq wrote: "Yummy"
	Ahsan Saeed wrote: "One pink tea for me"

--- Food Fusion is making Halwa Puri
"Sunday Special Breakfast for our followers..."
 ... (10/11/2017)

-----------------------------------
```

### 11. Search Functionality
```
Command: Search("Birthday")
Posts:
--- post8 - Shahem Riaz is celebrating a birthday
"Happy Birthday to my dear Mom" ... (14/11/2017)
--- post9 - Shahem Riaz is celebrating a birthday
"Happy Birthday to my dear Father" ... (14/10/2017)
--- post15 - Haris Muneer is celebrating a birthday
"Happy Birthday Ali Bhai" ... (10/10/2017)
-----------------------------------

Command: Search("Ali")
Users:
--- u6 - Saad Ali
--- u11 - Ahsan Saeed
--- u1 - Muhammad Ali
Posts:
--- post15 - Haris Muneer is celebrating a birthday
"Happy Birthday Ali Bhai" ... (10/10/2017)
Pages:
--- p2 - Al Jazeera English
-----------------------------------
```

## Learning Outcomes

This project helps understand:
- Class design and relationships
- Inheritance hierarchies
- Virtual functions and polymorphism
- Memory management in C++
- File I/O operations
- Dynamic arrays and pointers
- Copy constructors and assignment operators
- Const correctness

## Future Enhancements

- Add database support instead of text files
- Implement friend request system
- Add privacy settings for posts
- Create a GUI interface
- Add messaging functionality
- Implement notification system

## License

This is an academic project for educational purposes.

---
**Project Created**: January 2026  
**Course**: Object-Oriented Programming
