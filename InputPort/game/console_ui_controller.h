#pragma once
#include "System.h"
class UIScene;
class ConsoleUIController {
public:
	bool isSceneReallyOnStack(int target);
	int getFontForLanguage(int lang);
	void NavigateToHome(void);
	void SetupFont();
	void render();
	void getCleanupOnReload();
	bool IsReloadingSkin();
	void SetMenuDisplayed(int menuId, bool displayed);
	void CloseAllPlayersScenes(bool immediate);
	void tick();
	void CloseAllUIScenes();
	void ReloadSkin();
	void StartReloadSkinThread();
	bool IsExpectingOrReloadingSkin();
	void NavigateBack(int option, bool force, int EUIScene, int EUILayer );
	int GetTopScene();
	int GetTopScene2();
	void RegisterForCallbackId(void* uiscene);
	void CloseUIScenes(int sceneId, bool immediate);
	bool IsSceneInStack(int sceneId, int EUIScene);
	bool CheckMenuDisplayed();
	void PlayUISFX(int* soundEvent);
	/// <summary>
	/// [Extension] Play engine ui sound by using a pointer from the BANK <seealso cref="Sound"></seealso>
	/// </summary>
	void PlayUISFX(int sfxPtr);
	void ResetSelectedItem();
	bool IsTutorialVisible(int tutorialId);
	void ShowTrialTimer(bool show);
	void ShowUIDebugConsole(bool show);
	void RequestMessageBox(int a, int b, int c, int d, int e, int f);
	void RequestAlertMessage(int localized_message_string);
	/// <summary>
	/// Checks if an modal scene gots focus. 
	/// Example: Crafting menu
	/// </summary>
	/// <returns>Boolean</returns>
	static bool IsModalActive();
	UIScene* findScene(int EUIScene);
	UIScene* const checkGetSceneInstanceExRealLegitThisTimeCertifiedExtensionMethod(int EUIScene);
};

extern ConsoleUIController* const g_UIController;
