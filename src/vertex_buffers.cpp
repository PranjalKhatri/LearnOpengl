#include "vertex_buffers.hpp"

using namespace pop::gfx;

VertexBuffer::VertexBuffer() : buffer_id_{0} { glGenBuffers(1, &buffer_id_); }

VertexBuffer::~VertexBuffer() {
    if (buffer_id_ != 0) {
        glDeleteBuffers(1, &buffer_id_);
    }
}

void VertexBuffer::Bind(BufferType target) {
    glBindBuffer(static_cast<GLenum>(target), buffer_id_);
}

void VertexBuffer::BufferData(BufferType target, GLsizeiptr size,
                              const void* data, GLenum usage) {
    // Bind buffer first
    glBindBuffer(static_cast<GLenum>(target), buffer_id_);
    glBufferData(static_cast<GLenum>(target), size, data, usage);
}
