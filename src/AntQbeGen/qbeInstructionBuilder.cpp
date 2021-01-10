#include "./qbeInstructionBuilder.h"

QbeInstruction AntQbeInstructionBuilder::add(QbeTempType retType, QbeTemp resultTemp, QbeOperand leftOperand, QbeOperand rightOperand)
{
	//TODO: assert the types to catch possible error early
	return QbeInstruction{
		.kind = QbeInstructionKind::AddKind,
		.addIns = {
			.retType = retType,
			.result = resultTemp,
			.leftOperand = leftOperand,
			.rightOperand = rightOperand
		}
	};
}

QbeInstruction AntQbeInstructionBuilder::sub(QbeTempType retType, QbeTemp resultTemp, QbeOperand leftOperand, QbeOperand rightOperand)
{
	//TODO: assert the types to catch possible error early
	return QbeInstruction{
		.kind = QbeInstructionKind::SubKind,
		.subIns = {
			.retType = retType,
			.result = resultTemp,
			.leftOperand = leftOperand,
			.rightOperand = rightOperand
		}
	};
}

QbeInstruction AntQbeInstructionBuilder::mul(QbeTempType retType, QbeTemp resultTemp, QbeOperand leftOperand, QbeOperand rightOperand)
{
	//TODO: assert the types to catch possible error early
	return QbeInstruction{
		.kind = QbeInstructionKind::MulKind,
		.mulIns = {
			.retType = retType,
			.result = resultTemp,
			.leftOperand = leftOperand,
			.rightOperand = rightOperand
		}
	};
}

QbeInstruction AntQbeInstructionBuilder::div(QbeTempType retType, QbeTemp resultTemp, QbeOperand leftOperand, QbeOperand rightOperand)
{
	//TODO: assert the types to catch possible error early
	return QbeInstruction{
		.kind = QbeInstructionKind::DivKind,
		.divIns = {
			.retType = retType,
			.result = resultTemp,
			.leftOperand = leftOperand,
			.rightOperand = rightOperand
		}
	};
}
