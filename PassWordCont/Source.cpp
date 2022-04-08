#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "EnterField.h"
#include "Content_panel.h"
#include "Button.h"
#include "PasswordRNG.h"
#include "JsonIO.h"
#include "CheckBox.h"
#include "Encryption.h"
#include "MasterPassWizard.h"

const float WIDTH = 1280.0f;
const float HEIGHT = 720.0f;

int main()
{
    if (::IsWindowVisible(::GetConsoleWindow())) 
    {
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::Vector2f wind_asp = sf::Vector2f(WIDTH, HEIGHT);

    sf::Font font;
    font.loadFromFile("fonts\\font.ttf");

    sf::Font font_bold;
    font_bold.loadFromFile("fonts\\font_bold.ttf");

    std::string m_p = MasterPassWizard::get_enc_from_file("data\\master.pass");

    bool first_start = (m_p == "");

    sf::RenderWindow log_in_window(
        sf::VideoMode(WIDTH / 3, HEIGHT / 10), 
        (first_start ? "Set Master Password:" : "Enter Master Password:"), 
        sf::Style::Titlebar, settings);

    EnterField masterPasswordField;
    masterPasswordField = EnterField(
        font, 
        sf::String(first_start ? "Set Password" : "Enter Password"),
        sf::Vector2f(20.0f, 20.0f), 
        sf::Vector2f((WIDTH / 3) * 0.9f, 30.0f), 
        wind_asp,
        20);

    std::string first_pass = "";
    bool retried = false;

    while (log_in_window.isOpen())
    {
        sf::Event event;
        while (log_in_window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    log_in_window.close();
                    return 0;
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (!first_start) {
                        if (!masterPasswordField.is_fresh())
                        {
                            if (masterPasswordField.get_text() == m_p)
                            {
                                log_in_window.close();
                            }
                            else
                            {
                                masterPasswordField.set_text("Invalid password!");
                                masterPasswordField.set_passive();
                                masterPasswordField.set_fresh();
                            }
                        }
                    }
                    else 
                    {
                        if (!masterPasswordField.is_fresh())
                        {
                            if (!retried) 
                            {
                                first_pass = masterPasswordField.get_text();
                                masterPasswordField.set_text("Repeat Password");
                                masterPasswordField.set_passive();
                                masterPasswordField.set_fresh();
                                retried = true;
                            }
                            else 
                            {
                                if (masterPasswordField.get_text() == first_pass)
                                {
                                    MasterPassWizard::encrypt_and_write(masterPasswordField.get_text(), "data\\master.pass");
                                    log_in_window.close();
                                }
                                else 
                                {
                                    masterPasswordField.set_text("Incorrect Repeat");
                                    masterPasswordField.set_passive();
                                    masterPasswordField.set_fresh();
                                    retried = false;
                                }
                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (masterPasswordField.collided(sf::Mouse::getPosition(log_in_window)))
                    {
                        masterPasswordField.set_active();
                    }
                    else
                    {
                        masterPasswordField.set_passive();
                    }
                }
            }

            masterPasswordField.process_input(event);
        }

        log_in_window.clear(sf::Color::White);

        masterPasswordField.draw(log_in_window);

        log_in_window.display();
    }

    srand(time(nullptr));
    PasswordRNG p = PasswordRNG(20);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Passy", sf::Style::Titlebar, settings);

    sf::RectangleShape input_area;
    input_area.setPosition(0, 0);
    input_area.setSize(sf::Vector2f(WIDTH, 160.0f + 30.0f));
    input_area.setFillColor(sf::Color::White);

    sf::RectangleShape line;
    line.setPosition(0, 160.0f + 30.0f);
    line.setSize(sf::Vector2f(WIDTH, HEIGHT * 0.004f));
    line.setFillColor(sf::Color(230, 230, 230));

    std::vector<EnterField> fields;

    fields.push_back(EnterField(font, sf::String("Enter Resource"), sf::Vector2f(20.0f, 20.0f), sf::Vector2f(WIDTH * 0.6f, 30.0f), wind_asp));
    fields.push_back(EnterField(font, sf::String("Enter Login"), sf::Vector2f(20.0f, 80.0f), sf::Vector2f(WIDTH * 0.6f, 30.0f), wind_asp));
    fields.push_back(EnterField(font, sf::String("Enter Password"), sf::Vector2f(20.0f, 140.0f), sf::Vector2f(WIDTH * 0.6f, 30.0f), wind_asp));

    Button rnd_btn = Button(sf::Vector2f(WIDTH * 0.6f + 40.0f, 140.0f), sf::Vector2f(140, 30), sf::String("randomize"), font, wind_asp);
    Button ready_btn = Button(sf::Vector2f(WIDTH * 0.6f + 40.0f, 20.0f), sf::Vector2f(140, 110), sf::String("add"), font, wind_asp);

    CheckBox visible = CheckBox(sf::Vector2f(WIDTH * 0.6f + 200.0f, 20.0f), sf::Vector2f(30, 30), wind_asp);
    CheckBox with_symbols = CheckBox(sf::Vector2f(WIDTH * 0.6f + 200.0f, 80.0f), sf::Vector2f(30, 30), wind_asp);

    JsonIO password_json = JsonIO("data\\passwords.json");

    std::vector<Content_panel> panels = password_json.get_content(font, font_bold, wind_asp);

    sf::Text visible_text;

    visible_text.setFillColor(sf::Color(40, 40, 40));
    visible_text.setCharacterSize(23);
    visible_text.setPosition(WIDTH * 0.6f + 240.0f, 20.0f);
    visible_text.setFont(font);
    visible_text.setString("invisible passwords");

    sf::Text symbols_text;

    symbols_text.setFillColor(sf::Color(40, 40, 40));
    symbols_text.setCharacterSize(23);
    symbols_text.setPosition(WIDTH * 0.6f + 240.0f, 80.0f);
    symbols_text.setFont(font);
    symbols_text.setString("include symbols");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    for (auto& field : fields) 
                    {
                        if (field.collided(sf::Mouse::getPosition(window)))
                        {
                            field.set_active();
                        }
                        else
                        {
                            field.set_passive();
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    password_json.set_json(panels);
                    password_json.write_file();

                    window.close();
                }
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta < 0) 
                {
                    if (panels.back().get_height() > HEIGHT * 0.95f) {
                        for (auto& panel : panels)
                        {
                            panel.scroll_up();
                        }
                    }
                }
                else if (event.mouseWheel.delta > 0) 
                {
                    if (panels[0].get_height() < 160.0f + 30.0f) {
                        for (auto& panel : panels)
                        {
                            panel.scroll_down();
                        }
                    }
                }
                
            }

            for (auto& field : fields)
            {
                field.process_input(event);
            }

            for (auto& panel : panels)
            {
                panel.get_click(event, sf::Mouse::getPosition(window));
            }

            int deletion_mark = -1;

            for (int i = 0; i < panels.size(); i++)
            {
                if (panels[i].delete_btn.onclick(event, sf::Mouse::getPosition(window))) 
                {
                    deletion_mark = i;
                    break;
                }
            }

            if (deletion_mark != -1) 
            {
                panels.erase(panels.begin() + deletion_mark);
                for (size_t i = deletion_mark; i < panels.size(); i++)
                {
                    panels[i].set_index(panels[i].get_index() - 1);
                    panels[i].scroll_up();
                }
            }

            if (rnd_btn.onclick(event, sf::Mouse::getPosition(window))) 
            {
                if (fields[2].is_fresh()) 
                {
                    fields[2].unfresh();
                }
                fields[2].set_text(p.get_rand_password());
            }

            if (ready_btn.onclick(event, sf::Mouse::getPosition(window)))
            {
                if (!fields[0].get_text().isEmpty() && !fields[1].get_text().isEmpty() && !fields[2].get_text().isEmpty() &&
                    !fields[0].is_fresh() &&
                    !fields[1].is_fresh() &&
                    !fields[2].is_fresh())
                {
                    if (!panels.empty()) {
                        panels.push_back(Content_panel(sf::Vector2f(0.0f, panels.back().get_height() + HEIGHT * 0.1f),
                            sf::Vector2f(WIDTH, HEIGHT * 0.1f),
                            sf::String(fields[0].get_text()),
                            sf::String(fields[1].get_text()),
                            sf::String(fields[2].get_text()),
                            font,
                            font_bold,
                            wind_asp,
                            panels.size() + 1));
                    }
                    else 
                    {
                        panels.push_back(Content_panel(sf::Vector2f(0.0f, 160.0f + 30.0f),
                            sf::Vector2f(WIDTH, HEIGHT * 0.1f),
                            sf::String(fields[0].get_text()),
                            sf::String(fields[1].get_text()),
                            sf::String(fields[2].get_text()),
                            font,
                            font_bold,
                            wind_asp,
                            panels.size() + 1));
                    }
                    if (visible.get_state()) 
                    {
                        panels.back().set_pass_opacity(0);
                    }
                    
                    for (auto &field : fields)
                    {
                        field.set_text("");
                    }
                }
            }

            if (visible.onclick(event, sf::Mouse::getPosition(window)))
            {
                if (visible.get_state())
                {
                    for (auto &panel : panels)
                    {
                        panel.set_pass_opacity(0);
                    }
                }
                else 
                {
                    for (auto& panel : panels)
                    {
                        panel.set_pass_opacity(255);
                    }
                }
                fields[2].swap_string();
            }

            if (with_symbols.onclick(event, sf::Mouse::getPosition(window)))
            {
                p.swap_symbols();
            }
        }

        window.clear(sf::Color::White);

        for (auto& panel : panels)
        {
            panel.draw(window);
        }

        window.draw(input_area);
        window.draw(line);

        for (auto& field : fields)
        {
            field.draw(window);
        }

        rnd_btn.draw(window);
        ready_btn.draw(window);
        visible.draw(window);
        with_symbols.draw(window);

        window.draw(visible_text);
        window.draw(symbols_text);

        window.display();
    }

    return 0;
}