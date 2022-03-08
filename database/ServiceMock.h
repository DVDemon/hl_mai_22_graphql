#include <graphqlservice/JSONResponse.h>
#include <graphqlservice/GraphQLService.h>

#include "../GQL/GQLSchema.h"
#include "../GQL/QueryObject.h"
#include "../GQL/AuthorObject.h"

#include <atomic>
#include <memory>
#include <stack>
#include <string>

namespace graphql::database::object
{

    std::shared_ptr<graphql::service::Request> GetService();

    struct AuthorImpl
    {
        int _id = 0;
        std::string _first_name;
        std::string _last_name;
        std::string _email;
        std::string _title;

        void beginSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const
        {
        }
        void endSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const
        {
        }
        int getId([[maybe_unused]] service::FieldParams &&params) const
        {
            return _id;
        }
        std::string getFirst_name([[maybe_unused]] service::FieldParams &&params) const
        {
            return _first_name;
        }

        std::string getLast_name([[maybe_unused]] service::FieldParams &&params) const
        {
            return _last_name;
        }
        std::string getEmail([[maybe_unused]] service::FieldParams &&params) const
        {
            return _email;
        }
        std::string getTitle([[maybe_unused]] service::FieldParams &&params) const
        {
            return _title;
        }
    };

    struct QueryImpl
    {
        void beginSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const;
        void endSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const;
        std::shared_ptr<Author> getAuthor(std::optional<int> &&idArg) const;
        std::vector<std::shared_ptr<Author>> getAllAuthors() const;
        std::vector<std::shared_ptr<Author>> getSearch(std::string &&term1Arg, std::string &&term2Arg) const;
    };

}