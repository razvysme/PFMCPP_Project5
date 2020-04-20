/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3 and will take you through how to write code that doesn't leak as well as how to refactor. 

 Destructors

 If you didn't do Project3, write 3 UDTs below (where it asks for Copied UDTs) that have: 
        member functions,
        member variables, 
        constructors that initialize the members. 
        for() or while() loops that modify member variables
        
 Define your implementations of all functions OUTSIDE of the class. 
 Then do instruction 2)
 
 If you DID do Project 3, do instruction 1)
 
 1) Copy a few of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

	If you already did Chapter2 part 10 on Coliru and don't have a Project3, just grab some UDTs from your Coliru Ch2P10 submission. 
 
 3) add 2 new UDTs that use only the types you copied above.
 4) Add destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 5) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 6) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 7) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

/*
 copied UDT 1:
 */
 #include <iostream>
struct Effect
{
	std::string name;
	unsigned short number;
	float param1;
	float param2;

    struct Preset 
    {
        float param1, param2, effectNumber; 
        Preset()
        {
            param1 = 0;
            param2 = 0;
            std::cout << "Preset loaded" << std::endl;
        }
        ~Preset()
        {
            std::cout << "Preset destructed" << std::endl;
        }
    };
    Preset myPresset;


    Effect() 
    {
        param1 = 0; 
        param2 = 0;
        std::cout << "Effect created, parameters initialized to: " << param1 <<std::endl;
        number = 1;
    }
    ~Effect()
    {
        std::cout << "Effect destructed" << std::endl;
    }

    void savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName);
    void changePreset( float currentParam1, float currentParam2 );
    void ressetPresets(Effect effect);
};

void Effect::savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName)
{
    presetName.param1 = currentParam1;
    presetName.param2 = currentParam2;
    presetName.effectNumber = effectNumber;
    std::cout << "Preset " << presetName.effectNumber << " is saved!" << std::endl; 
}
void Effect::changePreset(float currentParam1, float currentParam2)
{
    param1 = currentParam1; //this is some getto getter/setter thing, right?
    param2 = currentParam2;
    std::cout << "Effect number changed to: " << number++ << std::endl;
}
void Effect::ressetPresets(Effect effect)
{   
    unsigned short currentEffectNr = effect.number;
    while( currentEffectNr < 3)
    {
        param1=0;
        param2=0;
        std::cout << "Effect number: " << currentEffectNr << " is reseted." <<std::endl;
        currentEffectNr++;        
    }
}
/*
 copied UDT 2:
 */
struct Filter
{
    std::string type;
    int order;
    bool bypassLED = false;
    float cutoff = 10000;

    Filter()
    {
        if(order==2)
            type = "Steiner-Parker";
        else
            type = "Ladder";
    }
    ~Filter()
    {
        std::cout << "Filter destructed" << std::endl;
    }
    std::string changeType( std::string currentType );
    void bypass();
    void changeCutoff( float );
};

std::string Filter::changeType( std::string currentType )
{
    std::cout << "Cutoff is: " << cutoff << std::endl;
    return currentType;
}

void Filter::bypass()
{
    bypassLED = true;
}

void Filter::changeCutoff(float newCutoff)
{
    if ( newCutoff < cutoff )
    {
        while ( newCutoff < cutoff )
        {
            cutoff -= 100;
            std::cout << "Cutoff decreaded by 100" << std::endl;
        }
    }
    else if( newCutoff * 0.99f < cutoff  && newCutoff * 1.01f > cutoff )  
    {
        std::cout << "Cutoff not changed." << std::endl;    
    }
    else
    {
        while ( cutoff < newCutoff )
        {
            cutoff += 100;
            std::cout << "Cutoff increaded by 100" << std::endl;
        }
    }   
}
/*
 copied UDT 3:
 */
#include <vector>
struct Wavetable 
{
    std::string name = "blank";
    std::vector < float > wavetable ;

    Wavetable()
    {
        std::cout << "Wavetable is created" << std::endl;
    }
     ~Wavetable()
    {
        std::cout << "Wavetable destructed" << std::endl;
    }

    float getCurrentSample( float waveSamples[] , int currentSampleNr );
    void applyEffect(Effect effect); 
    void populateWavetable(Wavetable destination);
};

float Wavetable::getCurrentSample( float waveSamples[], int currentSampleNr )
{
    return waveSamples[currentSampleNr];
}
void  Wavetable::applyEffect( Effect effect )
{
    effect.param1 = rand();
    effect.param2 = rand();
}
void Wavetable::populateWavetable( Wavetable destination )
{
    for( int i = 0; i < 4; i++ )
    {
        destination.wavetable.push_back(rand());
    }
    int i = 0;
    for(float& item : destination.wavetable)
    {
        i++;
        std::cout << "Wavetable at position " << i << " value is " << item << std::endl;
    }
}

/*
 new UDT 4:
 */

struct EffectsChain
{
    Effect firstEffect;
    Effect secondEffect;
    Filter filter;

    EffectsChain()
    {
        firstEffect.name = "Delay";
        firstEffect.param1 = rand();
        secondEffect.name = "Reverb";
        secondEffect.param1 = rand();
        std::cout << "Effects chain created" << std::endl; 
    }
    ~EffectsChain()
    {
        std::cout << "Effects chain destructed" << std:: endl;
        firstEffect.param1 = 0;
        firstEffect.param2 = 0;
        secondEffect.param1 = 0;
        secondEffect.param2 = 0;
        filter.changeType("Steiner-Parker");
    }
};

/*
 new UDT 5:
 */

 struct WavetableBank
 {
    Wavetable w1;
    Wavetable W2;

    WavetableBank()
    {
        std::cout << "Bank created" << std::endl;
    }

    ~WavetableBank()
    {
        std::cout << "Bank destroyed" << std::endl; 
    }
 };

 //main
int main()
{
    //Part 3
    Effect effect1;
    Effect effect2;
    Filter myLOP;
    //Part 5 
    EffectsChain effectsChain;
    WavetableBank wavetables;

    effect1.savePreset( 0.3f, 0.4f, 1, effect1.myPresset );
    effect1.changePreset(0.2f, 1.0f);
    effect1.ressetPresets(effect1);
    myLOP.changeCutoff(10000);

    std::cout << "good to go!" << std::endl;
}
