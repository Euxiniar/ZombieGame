//
// Created by aidan on 10/15/17.
//

#include "RenderingManager.h"

RenderingManager::RenderingManager(Renderer *renderer)
        :   m_renderer(renderer) { }

void RenderingManager::draw(std::pair<int, std::function<void(Renderer&)>> drawable)
{
    m_drawCallbacks.push_back(drawable);
}

struct sortDrawables
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return b.first > a.first; }
};

void RenderingManager::render() {
    std::sort(m_drawCallbacks.begin(), m_drawCallbacks.end(), sortDrawables());
    for(std::pair<int, std::function<void(Renderer&)>>& drawable : m_drawCallbacks) {
        drawable.second(*m_renderer);
    }
}

Renderer *RenderingManager::getRenderer() {
    return m_renderer;
}
