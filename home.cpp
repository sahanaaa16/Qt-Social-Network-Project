#include "home.h"
#include "ui_home.h"
#include "network.h"
#include <QWidget>

home::home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::home){
    ui->setupUi(this);

    garbage.readUsers("/Users/sahana/newhw4/HW4.txt");
    garbage.readPosts("/Users/sahana/newhw4/posts.txt");
    garbage.readSongs("/Users/sahana/newhw4/songs.txt");

    ui->profileWidget->setVisible(false);
    ui->backButton->setVisible(false);
    ui->addSongWidget->setVisible(false);
    ui->loginTextBox->setAlignment(Qt::AlignRight);
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &home::friendClicked);
    connect(ui->suggestedFriendsTable, &QTableWidget::cellClicked, this, &home::suggestedFriendClicked);
    connect(ui->songsTable, &QTableWidget::cellClicked, this, &home::songClicked);
    connect(ui->sharedSongsTable, &QTableWidget::cellClicked, this, &home::sharedSongClicked);
}

home::~home(){
    delete ui;
}


//pre: none
//post: checks if the name the user passes in is accurate
void home::on_loginButton_clicked(){

    ui->loginTextBox->setPlaceholderText("Enter your name here!");

    QString givenName = ui->loginTextBox->toPlainText(); //gets the name
    std::size_t userId = garbage.getId(givenName.toStdString());

    if(userId != 999){ //if user is valid
        numLogins++;
        if(numLogins == 1){ //if its the first time going around
            ogUser = garbage.getUser(userId);
        }
        currUser = garbage.getUser(userId); //will equal ogUser the first time
        ui->loginWidget->setVisible(false);
        ui->profileWidget->setVisible(true);
        profile();
        populateSuggestedFriends();
        populateSongs();
        //populateSharedSongs();
    }

    else{
        ui->loginTextBox->clear();
        ui->loginTextBox->setPlaceholderText("Please enter another name. The username you entered is not in our database.");
    }
}

void home::profile(){
    std::vector<std::size_t> friends = currUser->getFriends();
    ui->profileWidget->setVisible(true);
    std::string posts;

    //the if-else statements determine what the display looks like (if it is currUser ir ogUser)
    if(currUser == ogUser){
        ui->suggestedFriendsTitle->setVisible(true);
        ui->suggestedFriendsTable->setVisible(true);
        populateSuggestedFriends();
        ui->backButton->setVisible(false);
        ui->addFriendWidget->setVisible(false);
        //std::cout << "HELLOOOOOO";
        ui->profileHeading->setText("My Profile");
        ui->postsHeading->setText("My Posts");
        ui->friendsTitle->setText("My Friends");
        posts = garbage.displayPosts(ogUser->getName(), 5, false);
    }
    else{
        ui->addSongButton->setVisible(true);
        ui->suggestedFriendsTitle->setVisible(false); //don't suggest friends if you're on someone else's page
        ui->suggestedFriendsTable->setVisible(false);
        ui->backButton->setVisible(true);
        ui->addFriendWidget->setVisible(true);
        ui->profileHeading->setText(QString::fromStdString(currUser->getName()) + "'s Profile");
        ui->friendsTitle->setText(QString::fromStdString(currUser->getName()) + "'s Friends");
        ui->postsHeading->setText(QString::fromStdString(currUser->getName()) + "'s Posts");
        posts = garbage.displayPosts(currUser->getName(), 5, true);
        std::cout << "Posts: " << posts;
    }
    ui->addSongWidget->setVisible(false);
    ui->sharedSongsWidget->setVisible(false); //regardless of who the user is, hide the sharedSongs
    ui->postsDisplay->setText(QString::fromStdString(posts)); //regardless of who the user, display posts
    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setColumnWidth(0, 300);
    ui->suggestedFriendsTable->setColumnWidth(0, 300);
    ui->friendsTable->setRowCount(friends.size());

    for(std::size_t i = 0; i < friends.size(); i++){ //displays the friend List
        std::string currFriendName = garbage.getUser(friends[i])->getName();
        QTableWidgetItem *currFriend = new QTableWidgetItem(QString::fromStdString(currFriendName));
        ui->friendsTable->setItem(i,0, currFriend);
    }
}

void home::friendClicked(int row, int col){
    QString friendName = ui->friendsTable->item(row,col)->text(); //gets the name of the friend clicked
    ui->loginTextBox->setText(friendName);
    on_loginButton_clicked(); //makes the friend the curr User
}

void home::suggestedFriendClicked(int r, int c){
    QString potential = ui->suggestedFriendsTable->item(r,c)->text(); //gets the name of the friend clicked
    ui->loginTextBox->setText(potential);
    on_loginButton_clicked(); //makes the friend the curr User
}

void home::on_backButton_clicked(){
    std::size_t ugh = 3;
    garbage.suggestFriends(currUser->getId(), ugh);
    ui->loginTextBox->setText(QString::fromStdString(ogUser->getName()));
    ui->addSongWidget->setVisible(false);
    on_loginButton_clicked();
}

void home::on_addFriendButton_clicked(){
    ui->addFriendCheck->setText(" ");
    int before = ogUser->getFriends().size();
    ogUser->addFriend(currUser->getId());
    int after = ogUser->getFriends().size();

    if(before == after){
        ui->addFriendCheck->setText("Friend already added!");
    }

    else{
        ui->addFriendCheck->setText("Friend added!");
    }
}

void home::populateSuggestedFriends(){
    std::size_t ugh = 3;
    std::vector<std::size_t> possibleFren = garbage.suggestFriends(ogUser->getId(), ugh);
    ui->suggestedFriendsTable->setColumnCount(1);
    ui->suggestedFriendsTable->setRowCount(possibleFren.size());
    for(std::size_t i = 0; i < possibleFren.size(); i++){
        //std::cout << "SHOULD BE!";
        User *temp = garbage.getUser(possibleFren[i]);
        std::string newFriend = temp->getName();
        //std::cout << "HELLO" << newFriend;
        QTableWidgetItem *currFriend = new QTableWidgetItem(QString::fromStdString(newFriend));
        ui->suggestedFriendsTable->setItem(i,0, currFriend);
        //std::cout << "Showing suggested friend: " << newFriend;
    }
}

void home::populateSongs(){
    ui->songsTable->setColumnWidth(0, 450);
    ui->songsTable->setColumnCount(2);
    int size = currUser->getSongs().size();
    std::vector<std::size_t> songsList = currUser->getSongs();
    ui->songsTable->setRowCount(size+1);

    QTableWidgetItem *artistHeader = new QTableWidgetItem(QString::fromStdString("Artist"));
    QTableWidgetItem *titleHeader = new QTableWidgetItem(QString::fromStdString("Title"));
    ui->songsTable->setItem(0,1, artistHeader);
    ui->songsTable->setItem(0,0, titleHeader);

    for(int i = 0; i <= size; i++){
        song *temp = garbage.getSong(songsList[i]); //gets the song
        QTableWidgetItem *tempArtist = new QTableWidgetItem(QString::fromStdString(temp->getArtist()));
        QTableWidgetItem *tempTitle = new QTableWidgetItem(QString::fromStdString(temp->getTitle()));
        ui->songsTable->setItem(i+1,1, tempArtist);
        ui->songsTable->setItem(i+1,0, tempTitle);
        std::cout<< "SONG IS: " << tempTitle;
    }

    if(size == 0){
        ui->songsTable->setItem(1,0, new QTableWidgetItem(QString::fromStdString("No liked songs :/")));
    }
    ui->songsTable->resizeColumnsToContents();
}

void home::songClicked(int row, int col){
    std::vector<std::string> ans;
    if(col == 0){ //if we are clicking a title box, display who else liked the song
        QString songName = ui->songsTable->item(row,col)->text(); //gets the name of the song clicked
        std::string artist = garbage.getArtist(songName.toStdString());
        std::size_t songId = garbage.getSongId(songName.toStdString());
        lastSelectedSongId = songId;
        ui->sharedSongsHeading->setText("Who else liked " + songName + " by " + QString::fromStdString(artist));
        ans = sharedSongs(songId);
        ui->sharedSongsTable->setRowCount(ans.size());
    }

    if(col == 1){ //if we are clicking an artist box, display all other songs the artist has
        QString artistName = ui->songsTable->item(row,col)->text(); //gets the name of the artist clicked
        ui->sharedSongsHeading->setText("Other Songs made by " + artistName);
        ans = artistsSongs(artistName.toStdString());
        ui->sharedSongsTable->setRowCount(ans.size());
    }
    ui->sharedSongsTable->setColumnCount(1);
    ui->sharedSongsTable->resizeColumnsToContents();
    ui->sharedSongsWidget->setVisible(true);
    if(ogUser == currUser){
        ui->addSongWidget->setVisible(false);
    }
    else{
        ui->addSongWidget->setVisible(true);
    }


    for(std::size_t i = 0; i < ans.size(); i++){
        QTableWidgetItem *display = new QTableWidgetItem (QString::fromStdString(ans[i]));
        ui->sharedSongsTable->setItem(i,0, display);
    }
}

void home::on_addSongButton_clicked(){
    if(lastSelectedSongId != 99999){
        int before = ogUser->getSongs().size();
        ogUser->addSong(lastSelectedSongId);
        int after = ogUser->getSongs().size();

        if(before == after){
            ui->addSongCheck->setText("Song already added!");
        }

        else{
            ui->addSongCheck->setText("Song added!");
        }
    }
}

void home::sharedSongClicked(int row, int col){
    QString potential = ui->sharedSongsTable->item(row,col)->text(); //gets the name of the friend clicked
    ui->loginTextBox->setText(potential);
    on_loginButton_clicked(); //makes the friend the curr User
}

//pre: none
//post: gets a list of all the people that also share a song
std::vector<std::string> home::sharedSongs(std::size_t inputSong){
    std::vector<std::string> answer;
    for(std::size_t i = 0; i < garbage.numUsers(); i++){
        User *temp = garbage.getUser(i);
        std::vector<std::size_t> songList = temp->getSongs();
        for(std::size_t j = 0; j < songList.size(); j++){
            if(songList[j] == inputSong && (temp->getName() != currUser->getName())){
                if (std::find(answer.begin(), answer.end(), temp->getName()) == answer.end()){
                    answer.push_back(temp->getName());
                }
            }
        }
    }

    if(answer.size() == 0){
        answer.push_back("No shared likes.");
    }

    return answer;
}

//pre: none
//post: gets a list of all the songs an artist has in the database
std::vector<std::string> home::artistsSongs(std::string inputArtist){
    std::vector<std::string> answer;
    for(std::size_t i = 0; i < garbage.numSongs(); i++){
        song *temp = garbage.getSong(i);
        if(temp->getArtist() == inputArtist){
            answer.push_back(temp->getTitle());
        }
    }
    return answer;
}
