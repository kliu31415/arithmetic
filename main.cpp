#include <iostream>
#include <vector>
#include <algorithm>
#include "sdl_base.h"
#include "fundamentals.h"
using namespace std;
vector<int> gen_values(int minn, int maxn, int cnt)
{
    vector<int> res;
    int sum = 0;
    for(int i=0; i<cnt; i++)
    {
        int to_add = randz(minn, maxn) * randsign();
        while(sum + to_add <= 0)
            to_add = randz(minn, maxn) * randsign();
        sum += to_add;
        res.push_back(to_add);
    }
    return res;
}
int main()
{
    sdl_settings::load_config();
    initSDL();
    setWindowIcon(TTF_RenderText_Solid(getFont(5), "+-", SDL_Color{255, 0, 0}));
    const int minn = 10000, maxn = 99999;
    long long ans = 0;
    int fsz = 70;
    int num_answered = 0;
    int num_numbers = 5;
    auto values = gen_values(minn, maxn, num_numbers);
    while(true)
    {
        while(SDL_PollEvent(&input))
        {
            if(input.type == SDL_QUIT)
            {
                sdl_settings::output_config();
                return 0;
            }
            if(input.type == SDL_KEYDOWN)
            {
                auto key = input.key.keysym.sym;
                if(key == SDLK_BACKSPACE)
                {
                    ans /= 10;
                }
                if(key == SDLK_RETURN || key == SDLK_KP_ENTER)
                {
                    ans = 0;
                }
                else if(ans < 1e12)
                {
                    int val = -1;
                    switch(key)
                    {
                    case SDLK_0:
                    case SDLK_KP_0:
                        val = 0;
                        break;
                    case SDLK_1:
                    case SDLK_KP_1:
                        val = 1;
                        break;
                    case SDLK_2:
                    case SDLK_KP_2:
                        val = 2;
                        break;
                    case SDLK_3:
                    case SDLK_KP_3:
                        val = 3;
                        break;
                    case SDLK_4:
                    case SDLK_KP_4:
                        val = 4;
                        break;
                    case SDLK_5:
                    case SDLK_KP_5:
                        val = 5;
                        break;
                    case SDLK_6:
                    case SDLK_KP_6:
                        val = 6;
                        break;
                    case SDLK_7:
                    case SDLK_KP_7:
                        val = 7;
                        break;
                    case SDLK_8:
                    case SDLK_KP_8:
                        val = 8;
                        break;
                    case SDLK_9:
                    case SDLK_KP_9:
                        val = 9;
                        break;
                    }
                    if(val != -1)
                    {
                        ans = ans*10 + val;
                        if(ans == accumulate(values.begin(), values.end(), 0LL))
                        {
                            num_answered++;
                            ans = 0;
                            values = gen_values(minn, maxn, num_numbers);
                        }
                    }
                }
            }
        }
        renderClear(255, 255, 255);
        drawText(to_str(ans), 0, getWindowH() - getFontH(fsz), fsz);
        drawText("count:" + to_str(num_answered), 0, 0, fsz/2, 0, 0, 150);
        string time = seconds_to_str(getTicks() / 1000);
        drawText(time, getWindowW() - getTextW(time, fsz/2), 0, fsz/2, 0, 0, 150);
        for(size_t i=0; i<values.size(); i++)
            drawText((values[i]>0?" ":"") + to_str(values[i]), 0, getFontH(fsz/2) + i*getFontH(fsz), fsz, 0, 20+30*i, 0);
        updateScreen();
    }
    return 0;
}
