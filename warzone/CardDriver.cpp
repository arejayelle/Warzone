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
        deck->printDeck();
        
        cout << "Populating Deck"<<endl;
        populateDeck(deck);
        deck->printDeck();

        cout << "Checking Draw pile" << endl;
        deck->printDrawpile();

        cout << "Drawing 5 random cards" << endl;
        int handSize = 5;
        Hand* hand = new Hand(deck);
        populateHand(deck, hand, handSize);
        hand->printHand();
    
        cout << "Checking Draw pile" << endl;
        deck->printDrawpile();

        cout << "Playing all cards in hand" << endl;
        playAllHand(hand, handSize);

        cout << "Checking Draw pile" << endl;
        deck->printDrawpile();

        return 0;
}

    void populateDeck(Deck* deck)
    {
        SpyCard* spyCard= new SpyCard();
        BombCard* bombCard = new BombCard();
        ReinforcementCard* reinforcementCard = new ReinforcementCard();
        BlockadeCard* blockadeCard = new BlockadeCard();
        AirliftCard* airliftCard = new AirliftCard();
        DiplomacyCard* diplomacyCard = new DiplomacyCard();

        // add cards
        for (int i = 0; i < 4; i++) {        
            deck->add(spyCard);
            deck->add(bombCard);
            deck->add(reinforcementCard);
            deck->add(airliftCard);
            deck->add(blockadeCard);
            deck->add(diplomacyCard);
        }

        return;
    }

    void populateHand(Deck* deck, Hand* hand, int handSize) 
    {
        for (int i = 0;i < handSize;i++) 
        {
            int* cardID = deck->draw();
            hand->addCard(cardID);
            cout << "Adding " << deck->getFromCatalog(cardID)->getName()<<" ID " << (int) cardID << endl;
        }
    }

    void playAllHand(Hand* hand, int handSize)
    {
        for (size_t i = 0; i < handSize; i++)
        {
            hand->play(0);
        }
    }

}
