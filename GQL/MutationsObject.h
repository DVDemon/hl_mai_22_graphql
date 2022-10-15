// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef MUTATIONSOBJECT_H
#define MUTATIONSOBJECT_H

#include "GQLSchema.h"

namespace graphql::database::object {
namespace methods::MutationsHas {

template <class TImpl>
concept applyAddAuthorWithParams = requires (TImpl impl, service::FieldParams params, std::string first_nameArg, std::string last_nameArg, std::string emailArg, std::string titleArg)
{
	{ service::AwaitableScalar<std::string> { impl.applyAddAuthor(std::move(params), std::move(first_nameArg), std::move(last_nameArg), std::move(emailArg), std::move(titleArg)) } };
};

template <class TImpl>
concept applyAddAuthor = requires (TImpl impl, std::string first_nameArg, std::string last_nameArg, std::string emailArg, std::string titleArg)
{
	{ service::AwaitableScalar<std::string> { impl.applyAddAuthor(std::move(first_nameArg), std::move(last_nameArg), std::move(emailArg), std::move(titleArg)) } };
};

template <class TImpl>
concept beginSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.beginSelectionSet(params) };
};

template <class TImpl>
concept endSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.endSelectionSet(params) };
};

} // namespace methods::MutationsHas

class [[nodiscard]] Mutations final
	: public service::Object
{
private:
	[[nodiscard]] service::AwaitableResolver resolveAddAuthor(service::ResolverParams&& params) const;

	[[nodiscard]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard]] Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		[[nodiscard]] virtual service::AwaitableScalar<std::string> applyAddAuthor(service::FieldParams&& params, std::string&& first_nameArg, std::string&& last_nameArg, std::string&& emailArg, std::string&& titleArg) const = 0;
	};

	template <class T>
	struct [[nodiscard]] Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard]] service::AwaitableScalar<std::string> applyAddAuthor(service::FieldParams&& params, std::string&& first_nameArg, std::string&& last_nameArg, std::string&& emailArg, std::string&& titleArg) const final
		{
			if constexpr (methods::MutationsHas::applyAddAuthorWithParams<T>)
			{
				return { _pimpl->applyAddAuthor(std::move(params), std::move(first_nameArg), std::move(last_nameArg), std::move(emailArg), std::move(titleArg)) };
			}
			else
			{
				static_assert(methods::MutationsHas::applyAddAuthor<T>, R"msg(Mutations::applyAddAuthor is not implemented)msg");
				return { _pimpl->applyAddAuthor(std::move(first_nameArg), std::move(last_nameArg), std::move(emailArg), std::move(titleArg)) };
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::MutationsHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::MutationsHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Mutations(std::unique_ptr<const Concept>&& pimpl) noexcept;

	[[nodiscard]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard]] service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const final;
	void endSelectionSet(const service::SelectionSetParams& params) const final;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Mutations(std::shared_ptr<T> pimpl) noexcept
		: Mutations { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}

	[[nodiscard]] static constexpr std::string_view getObjectType() noexcept
	{
		return { R"gql(Mutations)gql" };
	}
};

} // namespace graphql::database::object

#endif // MUTATIONSOBJECT_H
