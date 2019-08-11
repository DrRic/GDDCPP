#include <vector>
class Node;
class Weight{
    private:
        double weight;
        Node* to;
        Node* from;
    public:
        Weight(double weight);
        double getProduct();
        double getWeight(){return weight;}
        void setTo(Node* to);        
        void setFrom(Node* from);
};

class Node{
    private:
        double value,output,error;
        vector<Weight *> weightsIn,weightsOut;
    public:
        Node();
        void addWeightIn(Weight* wp);
        void addWeightOut(Weight* wp);
        void setValue(double value);
        double getValue(){return value;}
        void calcValue();
};
