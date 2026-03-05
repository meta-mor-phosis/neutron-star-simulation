#include "raylib.h"
#include <math.h>

struct Particle{
    Vector2 pos;
    Vector2 vel;
};

int main(){

    const int width = 1200;
    const int height = 900;

    InitWindow(width,height,"Neutron Star Sandbox");

    Vector2 star = {width/2,height/2};

    float starMass = 20000;

    const int count = 4000;
    Particle p[count];

    for(int i=0;i<count;i++){

        float angle = GetRandomValue(0,360)*DEG2RAD;
        float radius = GetRandomValue(140,420);

        p[i].pos.x = star.x + cos(angle)*radius;
        p[i].pos.y = star.y + sin(angle)*radius;

        float speed = sqrt(starMass/radius);

        p[i].vel.x = -sin(angle)*speed;
        p[i].vel.y = cos(angle)*speed;
    }

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();

        DrawRectangle(0,0,width,height,(Color){0,0,0,18});

        for(int i=0;i<count;i++){

            Vector2 dir;

            dir.x = star.x - p[i].pos.x;
            dir.y = star.y - p[i].pos.y;

            float dist = sqrt(dir.x*dir.x + dir.y*dir.y);

            dir.x/=dist;
            dir.y/=dist;

            float gravity = starMass/(dist*dist);

            p[i].vel.x += dir.x*gravity;
            p[i].vel.y += dir.y*gravity;

            p[i].vel.x *= 0.999;
            p[i].vel.y *= 0.999;

            p[i].pos.x += p[i].vel.x;
            p[i].pos.y += p[i].vel.y;

            float speed = sqrt(p[i].vel.x*p[i].vel.x + p[i].vel.y*p[i].vel.y);

            Color c;

            if(speed < 2) c = BLUE;
            else if(speed < 4) c = ORANGE;
            else c = WHITE;

            DrawCircle(p[i].pos.x,p[i].pos.y,2,c);

            if(dist < 35){
                float angle = GetRandomValue(0,360)*DEG2RAD;
                float radius = GetRandomValue(200,420);

                p[i].pos.x = star.x + cos(angle)*radius;
                p[i].pos.y = star.y + sin(angle)*radius;

                float speed = sqrt(starMass/radius);

                p[i].vel.x = -sin(angle)*speed;
                p[i].vel.y = cos(angle)*speed;
            }
        }

        // neutron star glow
        DrawCircle(star.x,star.y,70,(Color){255,255,255,20});
        DrawCircle(star.x,star.y,45,(Color){255,255,255,40});
        DrawCircle(star.x,star.y,25,WHITE);

        // polar jets
        DrawRectangle(star.x-4,0,8,height,(Color){100,200,255,80});
        DrawRectangle(star.x-2,0,4,height,(Color){180,220,255,120});

        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

            Vector2 m = GetMousePosition();

            for(int i=0;i<50;i++){

                int id = GetRandomValue(0,count-1);

                p[id].pos = m;

                float angle = GetRandomValue(0,360)*DEG2RAD;

                p[id].vel.x = cos(angle)*3;
                p[id].vel.y = sin(angle)*3;
            }
        }
    }

    CloseWindow();
}