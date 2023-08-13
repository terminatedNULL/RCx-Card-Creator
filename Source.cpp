#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

#include "RCxUI.hpp"
#include "RCxSystem.hpp"

#include "FileWindow.hpp"
#include "FileHandler.hpp"
#include "FileErrorHandler.hpp"

#include "RCRD_Format.hpp"

#define NoWindow nullptr

using namespace RCxUI;

enum InnerWindows {
    FileDirWind,
    NewFileWind
};

//RCRDFile* loadRCRDFile(std::string path);
//RCRDFile* newProjectFile(std::string dirPath, CardTypes format, std::string name, std::string author);

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "RCx Card Creator", sf::Style::Fullscreen);
    ImGui::SFML::Init(window, sf::Vector2f(500, 500));

    RCRDFile* currentProjectFile;
    SystemEventHandler SysEvents(window);
    SystemStyleHandler SysStyle;
    FileErrorHandler errorHandler;

    bool windowActive = false;
    FileWindow* fileWindow = NoWindow;
    bool fileWindowActive = false;

    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    bool fullscreen = false;

    SysStyle.InitializeFonts();
    sf::Font bookFont = SysStyle.Fonts[SysFonts::Book];
        
    ImGui::GetIO().Fonts->Clear(); 
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets\\Fonts\\FiraSans-Bold.ttf", 20.f);
    ImGui::SFML::UpdateFontTexture(); 

    window.clear(BACKGROUND);

    //=============================================================================================
    // MAIN GUI
    //=============================================================================================
    int topOffset = SCREEN_HEIGHT / 20;
    int sideOffset = SCREEN_WIDTH / 35;

    sf::RectangleShape topBar(sf::Vector2f(SCREEN_WIDTH, topOffset));
    topBar.setPosition(sf::Vector2f(0, 0));
    topBar.setFillColor(FOREGROUND);

    sf::Text logo("RCx Card Creator", SysStyle.Fonts[SysFonts::SemiBold], 30);
    logo.setPosition(15, topBar.getSize().y / 4 - 6);
    logo.setFillColor(ACCENT);
    logo.setOutlineColor(sf::Color::Black);
    logo.setOutlineThickness(3);

    Line topBarLine(0, topOffset, SCREEN_WIDTH, topOffset);
    topBarLine.SetColor(TOP_GRADIENT);

    sf::RectangleShape sideBar(sf::Vector2f(sideOffset + 4, SCREEN_HEIGHT));
    sideBar.setPosition(sf::Vector2f(0, 0));
    sideBar.setFillColor(FOREGROUND);

    Line sideBarLine(sideOffset + 8, topOffset, sideOffset + 8, SCREEN_HEIGHT);
    sideBarLine.SetColor(TOP_GRADIENT);

    GradientRectangle topBarGradient(sideOffset, topOffset, SCREEN_WIDTH, topOffset + 40);
    topBarGradient.SetColor(FOREGROUND, FOREGROUND, BACKGROUND, BACKGROUND);

    int spacing = (SCREEN_HEIGHT - topOffset) / 10;
    std::vector<Line> sideLines;
    for (int i = 0; i < 10; i++) {
        sideLines.push_back(Line(0, topOffset + i * spacing, sideOffset, topOffset + i * spacing));
        sideLines[i].SetColor(TOP_GRADIENT);
    }

    //=============================================================================================
    // NEW FILE WINDOW
    //=============================================================================================

    unsigned int newFileWindActive = false;

    Textbox newFileName(
        (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 3) / 2 + 55,
        (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2 + 30,
        SCREEN_WIDTH / 3 - 60, 25, ""
    );
    newFileName.SetFont(SysStyle.Fonts[SysFonts::Italic]);
    newFileName.SetSingleLine(true);
    newFileName.SetOverflow(false);
    newFileName.SetCharacterSize(20);
    newFileName.BackgroundBorderDetails(TOP_GRADIENT, sf::Color::Transparent, 0);
    newFileName.SetColor(SECONDARY_TEXT);

    sf::Text nameText("Name", SysStyle.Fonts[SysFonts::SemiBold], 17);
    nameText.setPosition(sf::Vector2f(
        (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 3) / 2 + 5,
        (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2 + 30
    ));
    nameText.setFillColor(ACCENT);
    nameText.setOutlineColor(sf::Color::Black);
    nameText.setOutlineThickness(2);

    Button newFileCreateButton(
        (SCREEN_WIDTH / 2) - 25,
        (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2 + (SCREEN_HEIGHT / 1.5 - 25),
        50, 25, 0, "Create File",
        SysStyle.Fonts[SysFonts::SemiBold], 20
    );
    buttonBareBones(newFileCreateButton);

    //=============================================================================================
    // TESTING AND DEBUGGING
    //=============================================================================================

    //=============================================================================================
    // EVENT HANDLING
    //=============================================================================================
    sf::Clock deltaClock;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                if (newFileWindActive) { newFileName.TypedIn(event); }
                break;
            case sf::Event::MouseMoved:
                if (newFileWindActive) {
                    newFileCreateButton.Hover(window);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (newFileWindActive) { newFileName.Click(event, window); }
                break;
            case sf::Event::MouseButtonReleased:
                break;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //=============================================================================================
        // DRAW CALLS
        //=============================================================================================

        window.clear(sf::Color(18, 18, 18));

        ImGui::SetNextWindowSize(ImVec2(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowBgAlpha(0);

        ImGui::Begin("ImGui Window", nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar
        );

        window.draw(topBar);
        window.draw(sideBar);
        window.draw(logo);

        topBarGradient.Draw(window);
        topBarLine.Draw(window);
        sideBarLine.Draw(window);

        ImGui::SetCursorPos(ImVec2(4, SCREEN_HEIGHT / 20));

        ImGui::BeginGroup();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_TOP_GRADIENT);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_SECONDARY_TEXT);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_ACCENT);
        if (ImGui::Button("Name", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }
        
        if (ImGui::Button("Cost", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Type", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Attacks", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Flavor", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Rarity", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Image", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Border", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Backs", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        if (ImGui::Button("Extras", ImVec2(sideOffset, spacing - 4))) {
            if (windowActive) break;
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::EndGroup();

        ImGui::SetCursorPos(ImVec2(SCREEN_WIDTH - 220, 20));

        if (ImGui::Button("Load File", ImVec2(100, topOffset - 40))) {
            fileWindowActive = true;
            fileWindow = new FileWindow(FileWindow::SelectFile);
            //Create new RCRD file at save location
        }
        ImGui::SameLine();
        if (ImGui::Button("New File", ImVec2(100, topOffset - 40))) {
            //File window open for RCRD files
            //Load RCRD file
        }

        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

//=============================================================================================
// FUNCTIONS
//=============================================================================================

/*
RCRDFile* loadRCRDFile(std::string path) {
    //RCRDFile* loadFile = new RCRDFile(errorHandler, path);

    if (!loadFile->LoadFromFile()) {
        errorHandler.SetError(
            errorHandler.CreateError(
                ErrorType::OpenFailure,
                ErrorLevel::Warning,
                ErrorMessages[ErrorType::OpenFailure],
                path
            )
        );
    }
    
    return loadFile;
}

RCRDFile* newProjectFile(std::string dirPath, CardTypes format, std::string name, std::string author) {
    //RCRDFile* newFile = new RCRDFile(errorHandler, dirPath, format, name, author);

    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    newFile->SetModDate(
        localTime.tm_mday,
        localTime.tm_mon + 1,
        localTime.tm_year + 1900
    );

    newFile->WriteToFile();

    //Load in file to GUI elements

    return newFile;
}*/