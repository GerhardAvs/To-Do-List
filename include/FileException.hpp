#ifndef FILE_EXCEPTION_HPP
#define FILE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

/**
 * @brief Error thrown when a file (CSV export or log) cannot be opened or written.
 *
 * The window catches it and shows what() in a message box.
 */
class FileException : public std::runtime_error {
private:
    std::string filePath;

public:
    /**
     * @brief Builds the exception for a file that failed.
     *
     * @param filePath Path of the file that could not be used.
     * @param reason Short text explaining what failed.
     */
    FileException(const std::string& filePath, const std::string& reason)
        : std::runtime_error(reason + ": " + filePath),
          filePath(filePath) {
    }

    /**
     * @brief Gets the path of the file that failed.
     *
     * @return File path.
     */
    const std::string& getFilePath() const {
        return this->filePath;
    }
};

#endif  // FILE_EXCEPTION_HPP
