
#ifndef PLAYABLESEGMENT_H
#define PLAYABLESEGMENT_H

#include<iostream>
class PlayableSegment {
public:
    //对于能够连续播放的数据块
    //用该数据结构记录相关信息
    int start_block_id;		//记录连续播放数据块的第一个块的编号
    int length;				//记录连续播放数据块的长度

    PlayableSegment(int s, int l);
};

#endif // PLAYABLESEGMENT_H
