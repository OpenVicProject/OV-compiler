#pragma once

#include "SimpleGrammar.hpp"
#include "TriggerGrammar.hpp"
#include <lexy/dsl.hpp>

namespace ovdl::v2script::grammar {
	constexpr auto modifier_keyword = LEXY_KEYWORD("modifier", lexy::dsl::inline_<Identifier>);
	constexpr auto factor_keyword = LEXY_KEYWORD("factor", lexy::dsl::inline_<Identifier>);

	struct FactorStatement {
		static constexpr auto rule = factor_keyword >> lexy::dsl::equal_sign + lexy::dsl::p<Identifier>;
		static constexpr auto value = lexy::forward<ast::NodePtr>;
	};

	struct ModifierStatement {
		static constexpr auto rule =
			modifier_keyword >>
			lexy::dsl::curly_bracketed.list(
				lexy::dsl::p<FactorStatement> |
				lexy::dsl::p<TriggerStatement>);

		static constexpr auto value =
			lexy::as_list<std::vector<ast::NodePtr>> >>
			lexy::callback<ast::NodePtr>(
				[](auto&& list) {
					return make_node_ptr<ast::ModifierNode>(LEXY_MOV(list));
				});
	};
}