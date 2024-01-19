#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE

class home : public QMainWindow
{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();
    void profile();
    void friendClicked(int row, int col);
    void songClicked(int row, int col);
    void sharedSongClicked(int row, int col);
    void suggestedFriendClicked(int r, int c);
    void populateSuggestedFriends();
    void populateSongs();
    std::vector<std::string> artistsSongs(std::string inputArtist);
    std::vector<std::string> sharedSongs(std::size_t inputSong);

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();
    void on_addFriendButton_clicked();
    void on_addSongButton_clicked();

private:
    Ui::home *ui;
    Network garbage;
    //A social network object, a User object representing the logged in user, and a User object representing the user currently being displayed.
    User *currUser;
    User *ogUser;
    std::size_t lastSelectedSongId = 99999;
    int numLogins = 0;
};

#endif // HOME_H
