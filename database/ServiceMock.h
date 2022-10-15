#include <graphqlservice/JSONResponse.h>
#include <graphqlservice/GraphQLService.h>

#include "../GQL/GQLSchema.h"
#include "../GQL/QueryObject.h"
#include "../GQL/MutationsObject.h"
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
        std::shared_ptr<Author> getAuthor(service::FieldParams&& params, std::optional<int> &&idArg) const;
        std::optional<std::vector<std::shared_ptr<Author>>> getAllAuthors(service::FieldParams&& params) const;
        std::vector<std::shared_ptr<Author>> getSearch(service::FieldParams&& params, std::string &&term1Arg, std::string &&term2Arg) const;
    };

    struct MutationsImpl
    {
        void beginSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const;
        void endSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const;
        std::string applyAddAuthor(service::FieldParams&& params,
                                   std::string &&first_nameArg, std::string &&last_nameArg, std::string &&emailArg, std::string &&titleArg) const;
    };
    

}