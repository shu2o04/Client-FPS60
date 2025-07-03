#pragma once
#include "item_post.h"
class PostItem 
{
public:
	PostItem ();
	void Hook();
	static void Equipments();
	static void RemoveEquipment(void * item_data);
	static void PostItemToWorldChatChannel();
	static void PostItemToWorldChatChannelImp ( void * item_data );
	static void * AddItem ( void * item_data );
	static void BuildChatDataLong();  // long message
	static void BuildChatDataShort();  // short message
	static void BuildChatData ( void * chat_data_pointer );
	static void ProcessCharacterHeadChatText();
	void ClearSession();
	static void ProcessCharacterHeadChatTextImp ( char * base_address, char * chat_text );
	static void ViewPostItem();
	static void ViewPostItemImp ( void * chat_data_pointer );

	int PostItemColor;
	DWORD eItemNode[20];
	LinkedList<ItemPost> list_;
	unsigned long list_counter_;
	DWORD last_tickcount_post_;
	void ** current_item_post_;
	DWORD * last_tickcount_view_;
	bool draw_character_head_chat_text_;
	char * draw_character_head_chat_text_base_address_;
	DWORD last_tickcount_moveitem_;
}; extern PostItem gPostItem;