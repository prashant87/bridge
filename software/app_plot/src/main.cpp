#include <Ogre.h>
#include <OgreApplicationContext.h>

#include "ImguiManager.h"

class ImguiExample : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    void plotsWindow();
    void plotGroupCtrls( const char * title );
    void plotGroup( const char * title, const ImVec2 & sz=ImVec2( 320, 240 ), bool sameLine=false );

    ImguiExample() : OgreBites::ApplicationContext("OgreImguiExample")
    {
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        OgreBites::ApplicationContext::frameStarted(evt);

        Ogre::ImguiManager::getSingleton().newFrame(
            evt.timeSinceLastFrame,
            Ogre::Rect(0, 0, getRenderWindow()->getWidth(), getRenderWindow()->getHeight()));

        ImGui::ShowTestWindow();
        plotsWindow();

        return true;
    }

    void setup()
    {
        OgreBites::ApplicationContext::setup();
        addInputListener(this);

        Ogre::ImguiManager::createSingleton();
        addInputListener(Ogre::ImguiManager::getSingletonPtr());

        // get a pointer to the already created root
        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();
        Ogre::ImguiManager::getSingleton().init(scnMgr);

        // register our scene with the RTSS
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);


        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);


        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 15);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5); // specific to this sample
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);
        getRenderWindow()->addViewport(cam);

        Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(ent);
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt)
    {
        if (evt.keysym.sym == 27)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }
};


int main(int argc, char *argv[])
{
    ImguiExample app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();

    return 0;
}


void ImguiExample::plotsWindow()
{
    if ( !ImGui::Begin( "Plots", 0 ) )
        return;

    plotGroupCtrls( "Controls" );
    plotGroup( "Plot A", ImVec2( 0, 80 ), false );
    plotGroup( "Plot B", ImVec2( 0, 80 ), true );
    plotGroup( "Plot C", ImVec2( 0, 80 ), false );
    plotGroup( "Plot D", ImVec2( 0, 80 ), true );

    ImGui::End();
}

void ImguiExample::plotGroupCtrls( const char * title )
{
    ImGui::BeginGroup();
    {
        ImGui::Button( "Click me" );
    }
    ImGui::EndGroup();
}

void ImguiExample::plotGroup( const char * title, const ImVec2 & sz, bool sameLine )
{
    //if ( sameLine )
    //    ImGui::SameLine();

    ImGui::SetNextWindowSizeConstraints( ImVec2(0, 0), sz );

    //ImGui::BeginGroup();
    {
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        ImGui::PlotLines( "Curve", arr, IM_ARRAYSIZE(arr), 0, "avg 0.0", -1.0f, 1.0f, sz );
    }
    //ImGui::EndGroup();

    if ( ImGui::IsItemHovered() )
    {
        ImGui::BeginTooltip();
        {
            ImGui::TextUnformatted( title );
        }
        ImGui::EndTooltip();
    }
}

