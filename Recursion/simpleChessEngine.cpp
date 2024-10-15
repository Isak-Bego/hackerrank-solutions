#include "./stdc++.h"
using namespace std;

class Figure {
    vector< vector<int> > moveDirections; //based on the xy-axis
    bool scalableMoves = true; //only the knights moves are not scalable
    string name;
    char team;
    int pos[2] = {0};
public:
    vector< vector<int> > getMoveDirections() {
        return moveDirections;
    }
    void setMoveDirections(const vector< vector<int> > &d) {
        moveDirections = d;
    }
    void setName(const string &n) {
        name = n;
    }
    string getName() {
        return name;
    }
    void setScalableMoves(bool s) {
        scalableMoves = s;
    }
    bool doesScalableMoves() {
        return this->scalableMoves;
    }
    void setTeam(char t) {
        team = t;
    }
    char getTeam() {
        return team;
    }
    void setPos(int x, int y) {
        pos[0] = x;
        pos[1] = y;
    }
    int* getPos() {
        return pos;
    }

    bool isTheSame(Figure compare) {
        if(name == compare.getName() && pos[0] == compare.getPos()[0] && pos[1] == compare.getPos()[1]) {
            return true;
        }
        return false;
    }

};

class Queen : public Figure {
public:
    Queen(char t, int x, int y) {
        vector< vector<int> > moveDirections{{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
        setName("Queen");
        setScalableMoves(true);
        setMoveDirections(moveDirections);
        setTeam(t);
        setPos(x, y);
    }
};

class Bishop : public Figure {
public:
    Bishop(char t, int x, int y) {
        vector< vector<int> > moveDirections{{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
        setName("Bishop");
        setScalableMoves(true);
        setMoveDirections(moveDirections);
        setTeam(t);
        setPos(x, y);
    }
};

class Knight : public Figure {
public:
    Knight(char t, int x, int y) {
        vector< vector<int> > moveDirections{{1, 2}, {-1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, 1}, {-2, -1}};
        setName("Knight");
        setScalableMoves(false);
        setMoveDirections(moveDirections);
        setTeam(t);
        setPos(x, y);
    }
};

class Rook : public Figure {
public:
    Rook(char t, int x, int y) {
        vector< vector<int> > moveDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        setName("Rook");
        setScalableMoves(true);
        setMoveDirections(moveDirections);
        setTeam(t);
        setPos(x, y);
    }
};

class chessGame {
public:
    vector<Figure> whiteFigures;
    vector<Figure> blackFigures;
    int maxNumberOfMoves;
};


map<char, int> chessPositions = {
    {'1', 3}, {'2', 2}, {'3', 1}, {'4', 0}, {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}
};

//Works perfectly
//Gives you a vector of vectors that contain the original figure position in pos 0 and the new figure position in pos 1
//Account for the postions of the enemyfigures, because they can cover another their ally figure
//I LOVE THIS FUNCTION
vector< vector<Figure> > generatePossibleMoves(vector<Figure> teamFigures, vector<Figure> enemyFigures) {
    vector< vector<Figure> > possibleMoves;
    vector<Figure> move;
    Figure tf;
    Figure ef;
    for(int i = 0; i < teamFigures.size(); i++) {
        tf = teamFigures[i];
        int t = 1;
        if(tf.doesScalableMoves()) {
            t = 3;
        }
        for(int j = 0; j < tf.getMoveDirections().size(); j++) {
            for(int k = 1; k <= t; k++) {
                int x_new_pos = tf.getPos()[0] + (k * tf.getMoveDirections()[j][0]);
                int y_new_pos = tf.getPos()[1] + (k * tf.getMoveDirections()[j][1]);
                //Check if the move stays within the table
                if(x_new_pos <= 3 && y_new_pos <= 3 && x_new_pos >= 0 && y_new_pos >= 0) {
                    //register the move
                    bool allyOccupied = false;
                    bool enemyOccupied = false;
                    for(int l = 0; l < teamFigures.size(); l++) {
                        if(teamFigures[l].getPos()[0] == x_new_pos && teamFigures[l].getPos()[1] == y_new_pos) {
                            allyOccupied = true;
                            break;
                        }
                    }

                    for(int l =0; l < enemyFigures.size(); l++) {
                        if(enemyFigures[l].getPos()[0] == x_new_pos && enemyFigures[l].getPos()[1] == y_new_pos) {
                            enemyOccupied = true;
                            ef = enemyFigures[l];
                            break;
                        }
                    }

                    if(enemyOccupied) {
                        Figure temp = tf;
                        temp.setPos(x_new_pos, y_new_pos);
                        move.push_back(tf);
                        move.push_back(temp);
                        move.push_back(ef);
                        possibleMoves.push_back(move);
                        move.clear();
                        break;
                    }

                    if(!allyOccupied) {
                        Figure temp = tf;
                        temp.setPos(x_new_pos, y_new_pos);
                        move.push_back(tf);
                        move.push_back(temp);
                        possibleMoves.push_back(move);
                        move.clear();
                    }else {
                        break;
                    }
                }
            }
        }
    }
    return possibleMoves;
}

chessGame updateGame(chessGame currentGame, vector<Figure> currentMove) {
    vector<Figure>* allyFigures;
    vector<Figure>* enemyFigures;
    //identify team
    if (currentMove[0].getTeam() == 'w') {
        allyFigures = &currentGame.whiteFigures;
        enemyFigures = &currentGame.blackFigures;
    }else {
        allyFigures = &currentGame.blackFigures;
        enemyFigures = &currentGame.whiteFigures;
    }

    for(int i = 0; i < allyFigures->size(); i++) {
        if(allyFigures->at(i).getName() == currentMove[0].getName()
           && allyFigures->at(i).getPos()[0] == currentMove[0].getPos()[0]
           && allyFigures->at(i).getPos()[1] == currentMove[0].getPos()[1])
        {
            //update the position
            allyFigures->at(i).getPos()[0] = currentMove[1].getPos()[0];
            allyFigures->at(i).getPos()[1] = currentMove[1].getPos()[1];

            if(currentMove.size() == 3) {
                for(int j = 0; j < enemyFigures->size(); j++) {
                    if(enemyFigures->at(j).getName() == currentMove[2].getName()
                       && enemyFigures->at(j).getPos()[0] == currentMove[2].getPos()[0]
                       && enemyFigures->at(j).getPos()[1] == currentMove[2].getPos()[1])
                    {
                        enemyFigures->erase(enemyFigures->begin()+j);
                    }
                }
            }
        }
    }

    return currentGame;
}

bool nextTurn(chessGame game, int moveNumber, bool whiteTurn, bool queenIsKilled) {
    chessGame tempGame;
    bool answer = false;
    //TO-DO: Add a stopping condition when the moveNumber exceeds maxNumberOfMoves for the game
    if(moveNumber > game.maxNumberOfMoves) {
        return false;
    }

    //Determines which are the ally and enemy figures based on who has currently the turn
    vector<Figure> allyFigures, enemyFigures;

    if(whiteTurn) {
        allyFigures = game.whiteFigures;
        enemyFigures = game.blackFigures;
    }else {
        allyFigures = game.blackFigures;
        enemyFigures = game.whiteFigures;
    }

    vector< vector<Figure> > allyPossibleMoves = generatePossibleMoves(allyFigures, enemyFigures);
    //check if it can directly attack the queen, if so do it, remove the move from the possible moves and start looping the other moves
    for(int i = 0; i < allyPossibleMoves.size(); i++) {
        if(allyPossibleMoves[i].size() == 3 && allyPossibleMoves[i][2].getName() == "Queen") {
            tempGame = updateGame(game, allyPossibleMoves[i]);
            if(!whiteTurn) {
                return false;
            }
            answer = !nextTurn(tempGame, ++moveNumber, !whiteTurn, true);
            allyPossibleMoves.erase(allyPossibleMoves.begin()+i);
            if(whiteTurn && answer == true) {
                return answer;
            }
            return false;
        }
    }

    for(int i = 0; i < allyPossibleMoves.size(); i++) {
        answer = nextTurn(updateGame(game, allyPossibleMoves[i]), ++moveNumber, !whiteTurn, queenIsKilled);
        if(queenIsKilled) return answer;
        if(answer) return answer; 
    }

    return answer;
}

void processGame(chessGame* game) {
    bool result = nextTurn(*(game), 0, true, false);
    if(result == true) {
        cout<<"YES"<<endl;
    }else {
        cout<<"NO"<<endl;
    }
}

int main()
{
    vector<chessGame*> chessGames;
    int g, w, b, m;
    char figure, x_cord, y_cord;
    cin >> g;
    for(int i = 0; i < g; i++){
        chessGame* game = new chessGame();
        cin >> w >> b >> m;
        for(int j = 0; j < w; j++) {
            cin >> figure >> x_cord >> y_cord;
            Figure F;
            switch(figure) {
                case 'Q':
                    F = Queen('w', chessPositions[y_cord], chessPositions[x_cord]);
                    break;
                case 'N':
                    F = Knight('w', chessPositions[y_cord], chessPositions[x_cord]);
                    break;
                case 'B':
                    F = Bishop('w', chessPositions[y_cord], chessPositions[x_cord]);
                    break;
                case 'R':
                    F = Rook('w', chessPositions[y_cord], chessPositions[x_cord]);
                    break;
            }
            game->whiteFigures.push_back(F);
        }

        for(int j = 0; j < b; j++) {
            cin >> figure >> x_cord >> y_cord;
            Figure F;
            switch(figure) {
                case 'Q':
                    F = Queen('b', chessPositions[y_cord], chessPositions[x_cord]);
                break;
                case 'N':
                    F = Knight('b', chessPositions[y_cord], chessPositions[x_cord]);
                break;
                case 'B':
                    F = Bishop('b', chessPositions[y_cord], chessPositions[x_cord]);
                break;
                case 'R':
                    F = Rook('b', chessPositions[y_cord], chessPositions[x_cord]);
                break;
            }
            game->blackFigures.push_back(F);
        }
        game->maxNumberOfMoves = m;
        chessGames.push_back(game);
    }

    for(int i = 0; i < chessGames.size(); i++) {
        processGame(chessGames[i]);
    }

    return 0;
}
