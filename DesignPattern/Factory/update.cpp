//
// Created by Xhy_m on 2022/7/6.
//

#include "update.h"

bool update::start_update()
{
    get_update_url();
    cout << "update_url = " << update_url << endl;
    return true;
}
