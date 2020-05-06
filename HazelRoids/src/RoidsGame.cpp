#include "RoidsGame.h"
#include "ext\ExtensionFunctions.h"

#include "GameObject\UFO.h"
#include "GameObject\Asteroid.h"

#include "..\imgui\imgui.h"

namespace hzg
{
    float holdTime = 0.0f;
    float roidSpawnInterval = 0.0f;
    float ufoSpawnInterval = 0.0f;
    constexpr float maxHoldTime = 1.0f;
    constexpr float maxRoidSpawnInterval = 10.0f;
    constexpr float maxUfoSpawnInterval = 5.0f;
    constexpr char* youLoseTexts[5] = {
            "#   #  ###  #   #   #      ###   ####  ####",
            " # #  #   # #   #   #     #   # #     #    ",
            "  #   #   # #   #   #     #   #  ###  #####",
            "  #   #   # #   #   #     #   #     # #    ",
            "  #    ###   ###    #####  ###  ####   ####",
    };
    constexpr char* scoreText[5] = {
            " ####  ###  ###  ####   ####    ",
            "#     #    #   # #   # #     #  ",
            " ###  #    #   # ####  #####    ",
            "    # #    #   # #  #  #        ",
            "####   ###  ###  #   #  #### #  ",
    };

    void SpawnRandomUFO()
    {
        float x = ext::RNG32::NextFloat(0.0f, 1.7777777f * 2.0f) - 1.7777777f;
        float y = ext::RNG32::NextFloat(0.0f, 2.0f) - 1.0f;
        auto playerPos = RoidsGame::Get()->GetPlayer()->GetPosition();
        if (glm::abs(playerPos.x - x) < 1.0f && glm::abs(playerPos.y - y) < 1.0f)
        {
            if (x >= 0.0f) x += 1.0f;
            else x -= 1.0f;
        }
        RoidsGame::Get()->SpawnUFO({ x, y });
    }

    void SpawnRandomAsteroid()
    {
        float x = ext::RNG32::NextFloat(0.0f, 1.7777777f * 2.0f) - 1.7777777f;
        float y = ext::RNG32::NextFloat(0.0f, 2.0f) - 1.0f;

        auto playerPos = RoidsGame::Get()->GetPlayer()->GetPosition();
        if (glm::abs(playerPos.x - x) < 1.0f && glm::abs(playerPos.y - y) < 1.0f)
        {
            if (x >= 0.0f) x += 1.0f;
            else x -= 1.0f;
        }
        RoidsGame::Get()->SpawnRoid({ x, y });
    }

    RoidsGame* RoidsGame::s_Instance = nullptr;

    RoidsGame::RoidsGame()
        : Layer(), m_CameraController(16.0f / 9.0f)
    {
        Init();
    }

    RoidsGame* RoidsGame::Create()
    {
        if (s_Instance != nullptr)
        {
            HZ_WARN("RoidsGame Instance has already been created!");
        }
        else
        {
            s_Instance = new RoidsGame();
        }

        return s_Instance;
    }

    void RoidsGame::Init()
    {
        for (GameObject* obj : m_Objects)
            delete obj;
        for (Bullet* b : m_Bullets)
            delete b;
        m_Objects.clear();
        m_Bullets.clear();

        if (m_Player != nullptr) delete m_Player;
        
        m_Score = 0;
        m_LastScore = -1;


        m_Player = new Player();
        m_Player->SetMaxSpeed(1.0f);
        m_Player->SetAccelerationRate(0.5f);
        m_Player->SetRotationRate(180.0f);
        m_Player->SetReloadTime(0.2f);

        holdTime = 0.0f;
        roidSpawnInterval = 0.0f;
        ufoSpawnInterval = 0.0f;
    }

    void RoidsGame::SpawnUFO(const glm::vec2& _position)
    {
        UFO* ufo = new UFO();
        ufo->SetPosition({ _position.x, _position.y });
        ufo->SetMaxSpeed(0.5f);
        ufo->SetAccelerationRate(0.5f);
        ufo->SetReloadTime(1.0f);
        RoidsGame::Get()->AddGameObject(ufo);
    }

    void RoidsGame::SpawnRoid(const glm::vec2& _position, unsigned int _size)
    {
        Asteroid* roid = new Asteroid(_size);
        roid->SetPosition({ _position.x, _position.y });
        roid->SetRotation(ext::RNG32::NextFloat(0.0f, 360.0f));
        roid->SetMaxSpeed(0.5f);
        RoidsGame::Get()->AddGameObject(roid);
    }

    void RoidsGame::RenderScoreText() const
    {
        using namespace Hazel;
        constexpr float pixelWidth = 0.015f;
        glm::vec2 topLeft = { -1.6f, 0.85f };
        glm::vec4 color = { 1.0f, 1.0f, 0.1f, 1.0f };

        for (int i = 0; i < 5; ++i)
        {
            auto& str = m_ScoreTexts[i];

            for (int j = 0; j < str.length(); ++j)
            {
                if (str[j] == '#')
                {
                    Renderer2D::DrawQuad({ topLeft.x + pixelWidth * j, topLeft.y - pixelWidth * i }, { pixelWidth, pixelWidth }, color);
                }
            }
        }
    }

    void RoidsGame::RenderYouLoseText() const
    {
        using namespace Hazel;
        constexpr float pixelWidth = 0.03f;
        glm::vec2 center = { 0.0f, 0.0f };
        glm::vec2 topLeft = { -22.0f * pixelWidth, 2.5f * pixelWidth };
        glm::vec4 color = { 1.0f, 1.0f, 0.1f, 1.0f };

        for (int i = 0; i < 5; ++i)
        {
            const char* str = youLoseTexts[i];

            for (int j = 0; j < 44; ++j)
            {
                if (str[j] == '#')
                {
                    Renderer2D::DrawQuad({ topLeft.x + pixelWidth * j, topLeft.y - pixelWidth * i }, { pixelWidth, pixelWidth }, color);
                }
            }
        }
        Renderer2D::DrawQuad(center, { 44.0f * pixelWidth + 0.2f, 5.0f * pixelWidth + 0.2f }, { 0.3f, 0.3f, 0.3f, 0.5f });
    }

    void RoidsGame::OnAttach()
    {
        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    }

    void RoidsGame::OnDetach()
    {}
    
    void RoidsGame::OnUpdate(Hazel::Timestep _ts)
    {
        m_CameraController.OnUpdate(_ts);

        if (Hazel::Input::IsKeyPressed(Hazel::Key::LeftAlt))
        {
            m_ShowDebugGui = true;
        }
        else
        {
            m_ShowDebugGui = false;
        }

        if (Hazel::Input::IsKeyPressed(Hazel::Key::LeftControl) && Hazel::Input::IsKeyPressed(Hazel::Key::R))
        {
            holdTime += _ts;
            if (holdTime >= maxHoldTime)
            {
                // TODO: Restart game;
            }
        }
        else
        {
            holdTime = 0.0f;
        }

        if (holdTime >= maxHoldTime)
        {
            // restart the game;
            Init();
            holdTime = 0.0f;
        }

        if (!m_Player->IsDead())
        {
            if (Hazel::Input::IsKeyPressed(Hazel::Key::Up))
            {
                m_Player->SetAccelerating(1);
            }
            else if (Hazel::Input::IsKeyPressed(Hazel::Key::Down))
            {
                m_Player->SetAccelerating(-1);
            }
            if (Hazel::Input::IsKeyPressed(Hazel::Key::Left))
            {
                m_Player->SetRotating(1);
            }
            else if (Hazel::Input::IsKeyPressed(Hazel::Key::Right))
            {
                m_Player->SetRotating(-1);
            }
            if (Hazel::Input::IsKeyPressed(Hazel::Key::Space))
            {
                if (m_Player->IsReadyToShoot())
                {
                    m_Player->Shoot();
                }
            }

            // ===== Update World =====
            // ========================
            if (ufoSpawnInterval > maxUfoSpawnInterval)
            {
                SpawnRandomUFO();
                ufoSpawnInterval = 0.0f;
            }

            if (roidSpawnInterval > maxRoidSpawnInterval)
            {
                SpawnRandomAsteroid();
                roidSpawnInterval = 0.0f;
            }




            // ===== Update Game Objects =====
            // ===============================
            m_Player->Update(_ts);

            for (size_t i = 0; i < m_Bullets.size(); ++i)
            {
                m_Bullets[i]->Update(_ts);
                if (m_Bullets[i]->IsDead())
                {
                    m_Bullets.erase(m_Bullets.begin() + i);
                    --i;
                }
            }
            for (size_t i = 0; i < m_Objects.size(); ++i)
            {
                m_Objects[i]->Update(_ts);
                if (m_Objects[i]->IsDead())
                {
                    m_Objects.erase(m_Objects.begin() + i);
                    --i;
                }
            }


            // ===== Complete Updating Game Objects =====
            // ==========================================

            // ===== Check for Collision =====
            // ===============================
            for (int i = 0; i < m_Objects.size(); ++i)
            {
                if (!m_Player->IsDead())
                {
                    m_Player->Collide(m_Objects[i]);
                    if (m_Objects[i]->IsDead())
                    {
                        m_Score += m_Objects[i]->GetScore();
                        m_Objects.erase(m_Objects.begin() + i);
                        --i;
                    }
                }
                else break;
            }


            for (int i = 0; i < m_Bullets.size(); ++i)
            {
                for (int j = 0; j < m_Objects.size(); ++j)
                {
                    m_Bullets[i]->Collide(m_Objects[j]);
                    if (m_Objects[j]->IsDead())
                    {
                        m_Score += m_Objects[i]->GetScore();
                        m_Objects.erase(m_Objects.begin() + j);
                        --j;
                    }
                    if (m_Bullets[i]->IsDead())
                    {
                        m_Bullets.erase(m_Bullets.begin() + i);
                        --i;
                        break;
                    }
                }
            }



            // ===== Complete Collision Checking =====
            // =======================================

            roidSpawnInterval += _ts;
            ufoSpawnInterval += _ts;
        }

        if (m_Score > 999'999'999) m_Score = 999'999'999;
        #pragma region Update Score Text
        if (m_LastScore != m_Score)
        {
            m_ScoreTexts[0] = scoreText[0];
            m_ScoreTexts[1] = scoreText[1];
            m_ScoreTexts[2] = scoreText[2];
            m_ScoreTexts[3] = scoreText[3];
            m_ScoreTexts[4] = scoreText[4];

            char buffer[16];
            sprintf_s(buffer, "%09d", m_Score);
            for (int i = 0; i < 9; ++i)
            {
                switch (buffer[i])
                {
                    case '0':
                        m_ScoreTexts[0].append("  ### ");
                        m_ScoreTexts[1].append(" #  ##");
                        m_ScoreTexts[2].append(" # # #");
                        m_ScoreTexts[3].append(" ##  #");
                        m_ScoreTexts[4].append("  ### ");
                        break;
                    case '1':
                        m_ScoreTexts[0].append("  ##  ");
                        m_ScoreTexts[1].append(" # #  ");
                        m_ScoreTexts[2].append("   #  ");
                        m_ScoreTexts[3].append("   #  ");
                        m_ScoreTexts[4].append(" #####");
                        break;
                    case '2':
                        m_ScoreTexts[0].append(" #### ");
                        m_ScoreTexts[1].append("     #");
                        m_ScoreTexts[2].append("  ### ");
                        m_ScoreTexts[3].append(" #    ");
                        m_ScoreTexts[4].append(" #####");
                        break;
                    case '3':
                        m_ScoreTexts[0].append(" #### ");
                        m_ScoreTexts[1].append("     #");
                        m_ScoreTexts[2].append("  ### ");
                        m_ScoreTexts[3].append("     #");
                        m_ScoreTexts[4].append(" #### ");
                        break;
                    case '4':
                        m_ScoreTexts[0].append(" #  # ");
                        m_ScoreTexts[1].append(" #  # ");
                        m_ScoreTexts[2].append(" #####");
                        m_ScoreTexts[3].append("    # ");
                        m_ScoreTexts[4].append("    # ");
                        break;
                    case '5':
                        m_ScoreTexts[0].append(" #####");
                        m_ScoreTexts[1].append(" #    ");
                        m_ScoreTexts[2].append(" #### ");
                        m_ScoreTexts[3].append("     #");
                        m_ScoreTexts[4].append(" #### ");
                        break;
                    case '6':
                        m_ScoreTexts[0].append("  ### ");
                        m_ScoreTexts[1].append(" #    ");
                        m_ScoreTexts[2].append("  ### ");
                        m_ScoreTexts[3].append(" #   #");
                        m_ScoreTexts[4].append("  ### ");
                        break;
                    case '7':
                        m_ScoreTexts[0].append(" #####");
                        m_ScoreTexts[1].append(" #   #");
                        m_ScoreTexts[2].append("    # ");
                        m_ScoreTexts[3].append("   #  ");
                        m_ScoreTexts[4].append("  #   ");
                        break;
                    case '8':
                        m_ScoreTexts[0].append("  ### ");
                        m_ScoreTexts[1].append(" #   #");
                        m_ScoreTexts[2].append("  ### ");
                        m_ScoreTexts[3].append(" #   #");
                        m_ScoreTexts[4].append("  ### ");
                        break;
                    case '9':
                        m_ScoreTexts[0].append("  ### ");
                        m_ScoreTexts[1].append(" #   #");
                        m_ScoreTexts[2].append("  ### ");
                        m_ScoreTexts[3].append("     #");
                        m_ScoreTexts[4].append("  ### ");
                        break;
                }
}





            m_LastScore = m_Score;
        }
        #pragma endregion







        // ===== Draw =====
        // ================
        {
            using namespace Hazel;
            RenderCommand::Clear();
            Renderer2D::BeginScene(m_CameraController.GetCamera());
            Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.01f, 0.01f }, { 0.0f, 1.0f, 1.0f, 1.0f });

            // draw restart circle;
            {
                

                //ext::DrawCircle({ 0.0f, 0.0f }, 0.1f, { 0.0f, 1.0f, 1.0f, 1.0f }, 2.0f);
                float deg = holdTime / maxHoldTime * 360.0f;
                ext::DrawArc({ 0.0f, 0.0f }, 0.1f, 90.0f, 90.0f - deg, { 0.0f, 1.0f, 1.0f, 1.0f }, 2.0f);
            }

            if (m_Player->IsDead())
            {
                RenderYouLoseText();
                //Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.7777777f * 2.0f, 2.0f }, { 0.8f, 0.8f, 0.8f, 0.1f });
            }

            RenderScoreText();


            // draw player;
            m_Player->Render();
            m_Player->Render(true);

            // draw bullets;
            for (size_t i = 0; i < m_Bullets.size(); ++i)
            {
                m_Bullets[i]->Render();
                m_Bullets[i]->Render(true);
            }

            // draw the rest of game objects;
            for (size_t i = 0; i < m_Objects.size(); ++i)
            {
                m_Objects[i]->Render();
                m_Objects[i]->Render(true);
            }

            Renderer2D::EndScene();
        }
        // ===== Complete Drawing =====
        // ============================
    }

    void RoidsGame::OnImGuiRender()
    {
        if (!m_ShowDebugGui)
            return;

        if (m_Player->IsDead())
        {
            // show Dead guide window;
        }

        // always show score window;

        ImGui::ShowDemoWindow();
    }

    void RoidsGame::OnEvent(Hazel::Event& _event)
    {
        Hazel::EventDispatcher dispatcher(_event);

        dispatcher.Dispatch<Hazel::KeyReleasedEvent>([this] (Hazel::KeyReleasedEvent& _evt)
        {
            return false;
        });
    }
}
