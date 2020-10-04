#include "CardDriver.h"

int main()
{
    return Cards::main();
}
namespace Cards {

    int main()
    {
        Deck* deck = new Deck();
 
        cout << "Creating Deck"<<endl;
        
        cout << "Populating Deck"<<endl;
        cout << "Checking Draw pile" << endl;
        cout << "Drawing 5 cards" << endl;
        cout << "Checking Draw pile" << endl;
        return 0;
}

    void populateDeck(Deck* deck)
        return;
    }

    void populateHand(Deck* deck, Hand* hand, int handSize) 
    {
    }

    void playAllHand(Hand* hand, int handSize)
    {
        for (size_t i = 0; i < handSize; i++)
        {
            hand->play(0);
        }
    }

}
