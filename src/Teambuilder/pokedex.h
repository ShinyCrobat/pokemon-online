#ifndef POKEDEX_H
#define POKEDEX_H

#include <QtGui>

class TeamBuilder;
class TB_PokeChoice;
class GridBox;
class QImageButtonLR;

class Pokedex : public QWidget
{
    Q_OBJECT
public:
    Pokedex(TeamBuilder *parent);
};

class BigOpenPokeBall : public QLabel
{
    Q_OBJECT
public:
    BigOpenPokeBall();

    void update();
    bool shiny() const;
public slots:
    void changeToPokemon(int poke);
    void updatePicture();

private:
    int currentPoke;
    QLabel *num, *name;
    QLabel *specy;
    QLabel *height, *weight;
    QLabel *type1, *type2;
    QLabel *genderN, *genderF, *genderM;
    GridBox *front, *back;
    QCheckBox *shinyBox;
};

class PokedexBody : public QFrame
{
    Q_OBJECT

    enum {
        SortByNum = 0,
        SortByAlph = 1
    };
public:
    PokedexBody();

    void changeToPokemon(int poke);
public slots:
    void sortByColumn(int col);
private slots:
    void changeToPokemon(const QString &);
    void changePokemon();
    void changePokemonFromRow(int);
signals:
    void pokeChanged(int newPoke);
private:
    int currentPoke;
    TB_PokeChoice * pokeList;
    QLineEdit *pokeEdit;
};

class ProfileTab : public QFrame
{
    Q_OBJECT
public:
    ProfileTab();
public slots:
    void changeDesc (int poke);
private:
    QLabel *hgDesc, *ssDesc, *ptDesc;
    QLabel *ab1, *ab2;
};

class MoveTab : public QFrame
{
    Q_OBJECT
public:
    MoveTab();
};

class StatTab: public QFrame
{
    Q_OBJECT
public:
    StatTab();
public slots:
    void changePoke(int poke);
private:
    QLabel *min[6];
    QLabel *max[6];
    QImageButtonLR *buttons[6];
    QProgressBar *baseStats[6];
    int boost[6];
};

/* Just used for CSS */
class PokeBallDescBox : public QFrame
{
    Q_OBJECT
public:
    PokeBallDescBox() {}
    PokeBallDescBox(QWidget *parent) : QFrame(parent) {};
};

/* A box specially made to display 80*80 avatars */
/* Ripped off from AvatarBox (teambuilder.h) */
class GridBox : public QLabel {
public:
    GridBox(const QPixmap &pic=QPixmap(), bool shiftToBottom = false);

    void changePic(const QPixmap &pic);
protected:
    static QPixmap *background;
    QLabel *underLying;
};

/* A pokeball icon and a text */
class PokeBallText : public QWidget
{
public:
    PokeBallText(const QString &filename, const QString &text);
};

#endif // POKEDEX_H