#include "Engine/Engine.h"
#include "Engine/Localization.h"
#include "Engine/LOD.h"

#include "GUI/GUIWindow.h"
#include "GUI/GUIButton.h"
#include "GUI/GUIWindow.h"
#include "GUI/GUIFont.h"

#include "Platform/OSWindow.h"



struct GUIButton *pBtn_CloseBook;
struct GUIButton *pBtn_InstallRemoveSpell;
struct GUIButton *pBtn_Autonotes_Instructors;
struct GUIButton *pBtn_Autonotes_Misc;
struct GUIButton *pBtn_Book_6;
struct GUIButton *pBtn_Book_5;
struct GUIButton *pBtn_Book_4;
struct GUIButton *pBtn_Book_3;
struct GUIButton *pBtn_Book_2;
struct GUIButton *pBtn_Book_1;


struct GUIButton *pPlayerCreationUI_BtnReset;
struct GUIButton *pPlayerCreationUI_BtnOK;
struct GUIButton *pBtn_ExitCancel;
struct GUIButton *pBtn_YES;
struct GUIButton *pPlayerCreationUI_BtnPlus;
struct GUIButton *pPlayerCreationUI_BtnMinus;


struct GUIButton *pButton_RestUI_Main;
struct GUIButton *pButton_RestUI_Exit;
struct GUIButton *pButton_RestUI_Wait5Minutes;
struct GUIButton *pButton_RestUI_WaitUntilDawn;
struct GUIButton *pButton_RestUI_Wait1Hour;


struct GUIButton *pCharacterScreen_ExitBtn;
struct GUIButton *pCharacterScreen_AwardsBtn;
struct GUIButton *pCharacterScreen_InventoryBtn;
struct GUIButton *pCharacterScreen_SkillsBtn;
struct GUIButton *pCharacterScreen_StatsBtn;
struct GUIButton *pCharacterScreen_DollBtn;
struct GUIButton *pCharacterScreen_DetalizBtn;


struct GUIButton *pBtn_NPCRight;
struct GUIButton *pBtn_NPCLeft;
struct GUIButton *pBtn_GameSettings;
struct GUIButton *pBtn_QuickReference;
struct GUIButton *pBtn_CastSpell;
struct GUIButton *pBtn_Rest;
struct GUIButton *pBtn_History;
struct GUIButton *pBtn_Calendar;
struct GUIButton *pBtn_Maps;
struct GUIButton *pBtn_Autonotes;
struct GUIButton *pBtn_Quests;


struct GUIButton *pMMT_MainMenu_BtnMM6;
struct GUIButton *pMMT_MainMenu_BtnMM7;
struct GUIButton *pMMT_MainMenu_BtnMM8;
struct GUIButton *pMMT_MainMenu_BtnContinue;
struct GUIButton *pMMT_MainMenu_BtnExit;


struct GUIButton *pBtn_Up;
struct GUIButton *pBtn_Down;
struct GUIButton *ptr_507BA4;


GUIWindow *pPrimaryWindow;
GUIWindow *pChestWindow;
GUIWindow *pDialogueWindow;
GUIWindow *window_SpeakInHouse;
GUIWindow *pGUIWindow_ScrollWindow;
GUIWindow *ptr_507BC8;
GUIWindow *pGUIWindow_CurrentMenu;
GUIWindow *ptr_507BD0;
GUIWindow *pGUIWindow_CastTargetedSpell;
GUIWindow *pModalWindow;
GUIWindow *pGUIWindow_EscMessageWindow;
GUIWindow *pBooksButtonOverlay;
GUIWindow *pGUIWindow2;


struct GUIButton *pBtn_Resume;
struct GUIButton *pBtn_QuitGame;
struct GUIButton *pBtn_GameControls;
struct GUIButton *pBtn_LoadGame;
struct GUIButton *pBtn_SaveGame;
struct GUIButton *pBtn_NewGame;

struct GUIButton *pBtn_SliderRight;
struct GUIButton *pBtn_SliderLeft;


struct GUIButton *pBtnDownArrow;
struct GUIButton *pBtnArrowUp;
struct GUIButton *pBtnCancel;
struct GUIButton *pBtnLoadSlot;


std::array<GUIButton*, 4> pCreationUI_BtnPressRight2;
std::array<GUIButton*, 4> pCreationUI_BtnPressLeft2;
std::array<GUIButton*, 4> pCreationUI_BtnPressLeft;
std::array<GUIButton*, 4> pCreationUI_BtnPressRight;

void GUIButton::Release() {
  std::vector<GUIButton*>::iterator it = std::find(pParent->vButtons.begin(), pParent->vButtons.end(), this);
  if (it != pParent->vButtons.end()) {
    pParent->vButtons.erase(it);
  }
  delete this;
}

void GUIButton::DrawLabel(const String &label_text, GUIFont *pFont, int a5, int uFontShadowColor) {
  return pParent->DrawText(pFont,
    this->uX + (int)(this->uWidth - pFont->GetLineWidth(label_text)) / 2,
    this->uY + (int)(this->uHeight - pFont->GetHeight()) / 2,
    a5, label_text, 0, 0, uFontShadowColor);
}

bool GUIButton::Contains(unsigned int x, unsigned int y) {
  return (x >= uX && x <= uZ && y >= uY && y <= uW);
}

void CreateButtonInColumn( int column_pos, unsigned int control_id ) {
  pDialogueWindow->CreateButton( 480, 30 * column_pos + 146, 140, 30,  1,  0, UIMSG_SelectShopDialogueOption,  control_id, 0, "");
}

void ReleaseAwardsScrollBar() {
  if (awards_scroll_bar_created) {
    awards_scroll_bar_created = false;
    ptr_507BA4->Release();
    pBtn_Up->Release();
    pBtn_Down->Release();
    pBtn_Down = 0;
    pBtn_Up = 0;
    for (GUIButton *pButton : pGUIWindow_CurrentMenu->vButtons) {
      if (pButton->msg == UIMSG_InventoryLeftClick) {
        pButton->uX = dword_50698C_uX;
        pButton->uY = dword_506988_uY;
        pButton->uZ = dword_506984_uZ;
        pButton->uW = dword_506980_uW;
        pGUIWindow_CurrentMenu->_41D08F_set_keyboard_control_group(1, 0, 0, 0);
      }
    }
  }
}

void CreateAwardsScrollBar() {
  if (!awards_scroll_bar_created) {
    awards_scroll_bar_created = 1;
    for (GUIButton *pButton : pGUIWindow_CurrentMenu->vButtons) {
      if (pButton->msg == UIMSG_InventoryLeftClick) {
        dword_50698C_uX = pButton->uX;
        dword_506988_uY = pButton->uY;
        dword_506984_uZ = pButton->uZ;
        dword_506980_uW = pButton->uW;
        pButton->uW = 0;
        pButton->uZ = 0;
        pButton->uY = 0;
        pButton->uX = 0;
      }
    }
    pBtn_Up = pGUIWindow_CurrentMenu->CreateButton(438, 46,
      ui_ar_up_up->GetWidth(),
      ui_ar_up_up->GetHeight(),
      1, 0, UIMSG_ClickAwardsUpBtn, 0, 0, "",
      { {ui_ar_up_up, ui_ar_up_dn} });
    pBtn_Down = pGUIWindow_CurrentMenu->CreateButton(438, 292,
      ui_ar_dn_up->GetWidth(),
      ui_ar_dn_up->GetHeight(),
      1, 0, UIMSG_ClickAwardsDownBtn, 0, 0, "",
      { {ui_ar_dn_up, ui_ar_dn_dn} });
    ptr_507BA4 = pGUIWindow_CurrentMenu->CreateButton(440, 62, 16, 232, 1, 0, UIMSG_ClickAwardScrollBar, 0, 0, "");
  }
}

void UI_CreateEndConversationButton()
{
  pDialogueWindow->Release();
  pDialogueWindow = new GUIWindow(0, 0, window->GetWidth(), 345, 0);
  pBtn_ExitCancel = pDialogueWindow->CreateButton( 471, 445,  169, 35, 1, 0, UIMSG_Escape,  0,  0,
                 localization->GetString(74),  //"End Conversation"
    { {ui_exit_cancel_button_background} });
  pDialogueWindow->CreateButton(8, 8, 450, 320, 1, 0, UIMSG_BuyInShop_Identify_Repair, 0, 0, "");
}
