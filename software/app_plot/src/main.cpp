#include <Ogre.h>
#include <OgreApplicationContext.h>

#include "ImguiManager.h"
#include "plot_maker.h"
#include "classifier.h"
#include "al_wrap.h"

class ImguiExample : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    AlWrap    alWrap;
    PlotMaker plotMaker;
    Classifier classifier;
    std::vector<float> data[7];
    bool training;

    void plotRegressionWindow();

    void plotsWindow();
    void plotGroupCtrls( const char * title );
    void plotGroup( int index, const char * title, const ImVec2 & sz=ImVec2( 320, 240 ), bool sameLine=false );

    void plotsStdWindow();
    void plotStdGroupCtrls( const char * title );
    void plotStdGroup( int index, const char * title, const ImVec2 & sz=ImVec2( 320, 240 ), bool sameLine=false );

    ImguiExample() : OgreBites::ApplicationContext("Electrical analysis")
    {
        training = true;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        OgreBites::ApplicationContext::frameStarted(evt);

        Ogre::ImguiManager::getSingleton().newFrame(
            evt.timeSinceLastFrame,
            Ogre::Rect(0, 0, getRenderWindow()->getWidth(), getRenderWindow()->getHeight()));

        ImGui::ShowTestWindow();
        plotsWindow();
        plotsStdWindow();
        plotRegressionWindow();

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

        /*Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(ent);*/

        alWrap.createStream( &plotMaker );
    }

    bool keyPressed(const OgreBites::KeyboardEvent& evt)
    {
        if (evt.keysym.sym == 27)
        {
            getRoot()->queueEndRendering();
        }
        if ( training )
        {
            if ( ( evt.keysym.sym >= '1' ) && ( evt.keysym.sym <= '3' ) )
            {
                int category = evt.keysym.sym - '1';
                int rawQty, stdQty, step;
                classifier.dimensions( rawQty, stdQty, step );
                std::vector<float> data;
                plotMaker.classificationSample( rawQty, stdQty, step, data );
                classifier.push( category, data );
            }
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
    if ( ImGui::Begin( "Plots", 0 ) )
    {
        plotGroupCtrls( "Controls" );
        //plotGroup( 0, "Plot A", ImVec2(0, 180), false );
        //plotGroup( 1, "Plot B", ImVec2(0, 180), true );
        //plotGroup( 2, "Plot C", ImVec2(0, 180), false );
        plotGroup( 3, "Plot D", ImVec2( 0, 180 ), true );
        plotGroup( 4, "Plot E", ImVec2( 0, 180 ), true );
        plotGroup( 5, "Plot F", ImVec2( 0, 180 ), true );
        //plotGroup( 6, "Plot G", ImVec2( 0, 180 ), true );
    }
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

void ImguiExample::plotGroup( int index, const char * title, const ImVec2 & sz, bool sameLine )
{
    ImGui::BeginGroup();
        ImGui::PushID( index );
        if ( ImGui::Button( "up" ) )
            plotMaker.moveUp( index );
        ImGui::SameLine();
        if ( ImGui::Button( "+" ) )
            plotMaker.zoomIn( index );
        if ( ImGui::Button( "down" ) )
            plotMaker.moveDown( index );
        ImGui::SameLine();
        if ( ImGui::Button( "-" ) )
            plotMaker.zoomOut( index );
        if ( ImGui::Button( "|<" ) )
            plotMaker.setAudioSource( index );
        ImGui::PopID();
    ImGui::EndGroup();
    //if ( sameLine )
    //    ImGui::SameLine();

    ImGui::SameLine();
    //ImGui::SetNextWindowSizeConstraints( ImVec2(0, 0), sz );

    //ImGui::BeginGroup();
    {
        float vmin, vmax;
        plotMaker.limits( index, vmin, vmax );
        std::vector<float> & data = this->data[index];
        plotMaker.array( index, data );
        float * arr = data.data();
        const int qty = data.size();
        ImGui::PlotLines( "", arr, qty, 0, title, vmin, vmax, sz );
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

void ImguiExample::plotsStdWindow()
{
    if ( ImGui::Begin( "Plots std", 0 ) )
    {
        plotGroupCtrls( "Controls" );
        //plotStdGroup( 0, "Plot std A", ImVec2(0, 180), false );
        //plotStdGroup( 1, "Plot std B", ImVec2(0, 180), true );
        //plotStdGroup( 2, "Plot std C", ImVec2(0, 180), false );
        plotStdGroup( 3, "Plot std D", ImVec2( 0, 180 ), true );
        plotStdGroup( 4, "Plot std E", ImVec2( 0, 180 ), true );
        plotStdGroup( 5, "Plot std F", ImVec2( 0, 180 ), true );
        //plotStdGroup( 6, "Plot std G", ImVec2( 0, 180 ), true );
    }

    ImGui::End();
}

void ImguiExample::plotStdGroupCtrls( const char * title )
{

}

void ImguiExample::plotStdGroup( int index, const char * title, const ImVec2 & sz, bool sameLine )
{
    ImGui::BeginGroup();
        ImGui::PushID( index + 7 );
        if ( ImGui::Button( "up" ) )
            plotMaker.stdMoveUp( index );
        ImGui::SameLine();
        if ( ImGui::Button( "+" ) )
            plotMaker.stdZoomIn( index );
        if ( ImGui::Button( "down" ) )
            plotMaker.stdMoveDown( index );
        ImGui::SameLine();
        if ( ImGui::Button( "-" ) )
            plotMaker.stdZoomOut( index );
        ImGui::PopID();
    ImGui::EndGroup();
    //if ( sameLine )
    //    ImGui::SameLine();

    ImGui::SameLine();
    //ImGui::SetNextWindowSizeConstraints( ImVec2(0, 0), sz );

    //ImGui::BeginGroup();
    {
        float vmin, vmax;
        plotMaker.stdLimits( index, vmin, vmax );
        std::vector<float> & data = this->data[index];
        plotMaker.arrayStd( index, data );
        float * arr = data.data();
        const int qty = data.size();
        ImGui::PlotLines( "", arr, qty, 0, title, vmin, vmax, sz );
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

void ImguiExample::plotRegressionWindow()
{
    if ( ImGui::Begin( "Regression", 0 ) )
    {
        ImGui::BeginGroup();
        {
            ImGui::Checkbox( "Training", &training );
            if ( training )
            {
                ImGui::SameLine();
                ImGui::Text( "Use \"1\", \"2\", \"3\" buttons to add training data to a classifier" );
            }
            else
            {
                int rawQty, stdQty, step;
                classifier.dimensions( rawQty, stdQty, step );
                std::vector<float> data;
                plotMaker.classificationSample( rawQty, stdQty, step, data );
                int category = classifier.classify( data );

                ImGui::Text( "Category %i", category );
            }
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        {
            if ( ImGui::Button( "Load" ) )
            {
                classifier.load( "./classifier.data" );
            }
            ImGui::SameLine();
            if ( ImGui::Button( "Save" ) )
            {
                classifier.save( "./classifier.data" );
            }
        }
        ImGui::EndGroup();
    }

    ImGui::End();

}


