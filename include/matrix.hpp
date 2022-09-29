#ifndef AE6C5E93_D8A2_4875_9EB4_257B17DAEAD1
#define AE6C5E93_D8A2_4875_9EB4_257B17DAEAD1

#include <ostream>
#include <sstream>

namespace lib
{
    template <typename T>
    class Matrix
    {
    private:
        T **values = nullptr;
        size_t lines = 0, columns = 0;

        T formatValue(const T &value) const noexcept
        {
            return value;
        }

    public:
        Matrix() {}
        Matrix(size_t lines, size_t columns) : lines(lines), columns(columns)
        {
            this->alloc(lines, columns);
        }
        ~Matrix()
        {
            this->erase();
        }

        void alloc(size_t lines, size_t columns)
        {
            this->lines = lines;
            this->columns = columns;

            values = new T *[columns];
            for (size_t i = 0; i < columns; ++i)
                values[i] = new T[lines];

            defaults();
        }
        void erase()
        {
            for (size_t i = 0; i < columns; ++i)
                delete[] values[i];
            delete[] values;

            this->values = nullptr;
            this->lines = 0;
            this->columns = 0;
        }

        void defaults()
        {
            for (size_t i = 0; i < columns; ++i)
                for (size_t j = 0; j < lines; ++j)
                    values[i][j] = T();
        }
        T get(size_t line, size_t col) const
        {
            return this->values[line][col];
        }

        T &at(size_t line, size_t col)
        {
            return this->values[line][col];
        }
        std::string str() const
        {
            std::stringstream stream;
            stream << "[";
            if (columns > 1)
                stream << std::endl;

            for (size_t i = 0; i < columns; ++i)
            {
                stream << "\t[";
                for (size_t j = 0; j < lines; ++j)
                {
                    stream << formatValue(values[i][j]);
                    if (j < lines - 1)
                        stream << ", ";
                }
                stream << "]";
                if (i < columns - 1)
                    stream << ",";
                stream << std::endl;
            }
            stream << "]" << std::endl;

            return stream.str();
        }

        friend std::ostream &operator<<(std::ostream &o, const Matrix<T> &matrix)
        {
            o << matrix.str();
            return o;
        }
    };

    template <>
    std::string Matrix<std::string>::formatValue(const std::string &value) const noexcept
    {
        return "\"" + value + "\"";
    }
}

#endif /* AE6C5E93_D8A2_4875_9EB4_257B17DAEAD1 */
