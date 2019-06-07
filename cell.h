
class Cell{
    private:
        bool visited;
        bool eastWall;
        bool southWall;
    public:
        Cell();
        bool getVisited();
        void setVisited();
        void removeWall(int direction);
        bool getWall(int direction);
};