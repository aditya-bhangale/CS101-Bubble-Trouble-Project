#include <simplecpp>
#include "shooter.h"
#include "bubble.h"
#include <string>
using namespace std;
int health=3,score=0;
double time=0;
/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);
    //string healthpr("Health:");
    Text healthstring(LEFT_MARGIN+100, BOTTOM_MARGIN,"Health: ");
    Text healthvalue(LEFT_MARGIN+100+textWidth ("Health: "), BOTTOM_MARGIN,"3");
    Text timestring(LEFT_MARGIN+100+textWidth ("Health: ")+50,BOTTOM_MARGIN,"Time: ");
    Text timevalue(LEFT_MARGIN+100+textWidth ("Health: ")+50+textWidth("Time: "), BOTTOM_MARGIN, 0);
    Text scorestring(LEFT_MARGIN+100+textWidth ("Health: ")+50+textWidth("Time: ")+50,BOTTOM_MARGIN,"Score: ");
    Text scorevalue(LEFT_MARGIN+100+textWidth ("Health: ")+50+textWidth("Time: ")+50+textWidth("Score: "), BOTTOM_MARGIN, 0);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;
    int x_bub,y_bub,x_manhead,y_manhead,x_manbody,y_manbody,bodywidth,bodyheight,x_bull,y_bull,r_bub,headsizeman;

    // Main game loop
    while (true)
    {
        bool healthdecrease=0,scoreincrease=0;
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        for (unsigned int i=0; i < bubbles.size(); i++)
        {
        x_bub=bubbles[i].get_center_x();
        y_bub=bubbles[i].get_center_y();
        r_bub=bubbles[i].get_radius();


        for(unsigned int j=0; j<bullets.size(); j++)
        {
            x_bull=bullets[j].get_center_x();
            y_bull=bullets[j].get_center_y();
            //std::cout<<"hello";

            if(fabs(x_bub-x_bull)<(r_bub)&&fabs(y_bub-y_bull)<r_bub)
            {
            cout<<"H";

            bubbles.push_back(Bubble(x_bub+50, y_bub, BUBBLE_DEFAULT_RADIUS*0.5, -BUBBLE_DEFAULT_VX*5, 0, COLOR(255,105,180)));
            bubbles.push_back(Bubble(x_bub-50, y_bub, BUBBLE_DEFAULT_RADIUS*0.5, +BUBBLE_DEFAULT_VX*5, 0, COLOR(255,105,180)));
            bubbles[i].delete_bubble();
            bullets[j].delete_bullet();
            scoreincrease=1;
            scorevalue.setMessage((score));
            score++;
            }
            x_manhead=shooter.get_head_center_x();
            y_manhead=shooter.get_head_center_y();
            x_manbody=shooter.get_body_center_x();
            y_manbody=shooter.get_body_center_y();
            bodywidth=shooter.get_body_width();
            bodyheight=shooter.get_body_height();
            headsizeman=shooter.get_head_radius();
            //bool headbubble=(fabs(x_bub-x_manhead)<(r_bub+headsizeman))&&(fabs(y_bub-y_manhead)<r_bub+headsizeman);

            bool headbubble=(x_bub-x_manhead)*(x_bub-x_manhead)+(y_bub-y_manhead)*(y_bub-y_manhead)<(r_bub+headsizeman)*(r_bub+headsizeman);
            bool bodybubble=(abs(x_bub-x_manbody)<(r_bub+(bodywidth/2.0)))&&(abs(y_bub-y_manbody)<r_bub+(bodyheight/2.0));
            if(headbubble||bodybubble)
            {
                health--;
                healthdecrease=1;

                cout<<health;
                //break;
            }



        }
        }
        if(healthdecrease=1)
        {
            healthvalue.setMessage(to_string(health));
            healthdecrease=0;

        }


        //Text healthvalue(LEFT_MARGIN+100+textWidth ("Health: "), BOTTOM_MARGIN, health);

        //Text timevalue(LEFT_MARGIN+100+textWidth ("Health: ")+50+textWidth("Time: "), BOTTOM_MARGIN, int(time));

        //Text scorevalue(LEFT_MARGIN+100+textWidth ("Health: ")+50+textWidth("Time: ")+50+textWidth("Score: "), BOTTOM_MARGIN, score);
        time+=STEP_TIME*2;



        //wait(STEP_TIME/4);



}}
