#pragma once

#include <vector>
#include <cstdint>

#include <util.hpp>

#include <cg/geometry.hpp> // Vector2


namespace cg {

    struct Triangulation {
        Triangulation();
        ~Triangulation();

        // Triangula se necess�rio (retorna true se cache v�lido ap�s a chamada)
        // 'contour' � o anel exterior (n�o inclui buracos). quant � o passo de quantiza��o.
        bool triangulateIfNeeded(const std::vector<Vector2>& contour, float quant = 1e-3f);

        // For�a invalida��o do cache
        void invalidate();

        // Acessores ao resultado (v�rtices e �ndices dos tri�ngulos)
        const std::vector<Vector2>& verts() const { return triVerts_; }
        const std::vector<int>& indices() const { return triIndices_; }
        bool valid() const { return valid_; }

    private:
        // --- cache ---
        uint64_t lastHash_;
        std::vector<int64_t> lastQuant_;
        std::vector<Vector2> triVerts_;
        std::vector<int> triIndices_;
        bool valid_;

        // Quantiza��o / hashing helpers
        static void quantizePolygon(const std::vector<Vector2>& pts, std::vector<int64_t>& outQuant, float quant);
        static uint64_t fnv1a64(const void* data, size_t len);
        static uint64_t hashQuantized(const std::vector<int64_t>& q);

        // GLU tessellation internals
        struct TessVertex {
            GLdouble coord[3];
            int idx;
        };

        // pointer "current" para callbacks (thread local para seguran�a se for multithread)
        static thread_local Triangulation* s_current_;

        // callbacks
        static void CALLBACK beginCB(GLenum type);
        static void CALLBACK vertexCB(const GLvoid* data);
        static void CALLBACK endCB();
        static void CALLBACK errorCB(GLenum errCode);
        static void CALLBACK combineCB(GLdouble coords[3], void* vertex_data[4], GLfloat weight[4], void** outData);

        // executa GLU tessellator de fato; popula triVerts_ e triIndices_
        bool runGluTessellate(const std::vector<Vector2>& contour);

        // gerencia aloca��es relativas � tessela��o (TessVertex*)
        std::vector<TessVertex*> allocated_;

        // passo de quantiza��o atualmente usado (guardado para refer�ncia, opcional)
        float lastQuantStep_;
    };

} // namespace cg
