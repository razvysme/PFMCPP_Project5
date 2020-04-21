/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via 'this->' and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
        d) you should see 2 (almost) identical messages in the program output for each member function you add:
            one for the std::cout line, and one for the member function's output
 
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}



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
    Effect();
    ~Effect();

    struct Preset 
    {
        float param1, param2, effectNumber; 
        Preset();
        ~Preset();

    };
    Preset myPresset;
    void savePreset( float currentParam1, float currentParam2, float effectNumber, Preset presetName);
    void changePreset( float currentParam1, float currentParam2 );
    void ressetPresets(Effect effect);
};

Effect::Effect() 
{
    param1 = 0; 
    param2 = 0;
    std::cout << "Effect created, parameters initialized to: " << param1 <<std::endl;
    number = 1;
}

Effect::~Effect()
{
    std::cout << "Effect destructed" << std::endl;
}

Effect::Preset::Preset()
{
    param1 = 0;
    param2 = 0;
    std::cout << "Preset loaded" << std::endl;
}

Effect::Preset::~Preset()
{
    std::cout << "Preset destructed" << std::endl;
}

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
    Filter();
    ~Filter();

    std::string changeType( std::string currentType );
    void bypass();
    void changeCutoff( float );
};

Filter::Filter()
{
    if(order==2)
        type = "Steiner-Parker";
    else
        type = "Ladder";
}

Filter::~Filter()
{
    std::cout << "Filter destructed" << std::endl;
}

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

    Wavetable();
    ~Wavetable();

    float getCurrentSample( float waveSamples[] , int currentSampleNr );
    void applyEffect(Effect effect); 
    void populateWavetable(Wavetable destination);
};

Wavetable::Wavetable()
{
    std::cout << "Wavetable is created" << std::endl;
}

Wavetable::~Wavetable()
{
    std::cout << "Wavetable destructed" << std::endl;
}

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

    EffectsChain();
    ~EffectsChain();
};

EffectsChain::EffectsChain()
{
    firstEffect.name = "Delay";
    firstEffect.param1 = rand();
    secondEffect.name = "Reverb";
    secondEffect.param1 = rand();
    std::cout << "Effects chain created" << std::endl; 
}

EffectsChain::~EffectsChain()
{
    std::cout << "Effects chain destructed" << std:: endl;
    firstEffect.param1 = 0;
    firstEffect.param2 = 0;
    secondEffect.param1 = 0;
    secondEffect.param2 = 0;
    filter.changeType("Steiner-Parker");
}

/*
 new UDT 5:
 */
struct WavetableBank
{
    Wavetable w1;
    Wavetable W2;

    WavetableBank();
    ~WavetableBank();
};

WavetableBank::WavetableBank()
{
    std::cout << "Bank created" << std::endl;
}

WavetableBank::~WavetableBank()
{
    std::cout << "Bank destroyed" << std::endl; 
}

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
